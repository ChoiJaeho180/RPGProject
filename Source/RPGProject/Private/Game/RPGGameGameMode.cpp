// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/RPGGameGameMode.h"
#include "Game/RPGGameController.h"
#include "Game/RPGGameCharacter.h"
#include "Common/RPGCommonGameInstance.h"
#include "Game/RPGGamePlayerState.h"
#include "Common/REST/RPGCommonSerializeData.h"
#include "GameFramework/Controller.h"
#include "Game/RPGGameVillageInfo.h"
#include "Game/RPGGameHuntMapInfo.h"

ARPGGameGameMode::ARPGGameGameMode()
{
	PlayerControllerClass = ARPGGameController::StaticClass();
	DefaultPawnClass = ARPGGameCharacter::StaticClass();
	MapInfoClass = URPGGameMapInfo::StaticClass();
	GameNPCClass = ARPGGameNPC::StaticClass();
	GameNPCShopClass = ARPGGameNPCShop::StaticClass();
	GameNPCQuestClass = ARPGGameNPCQuest::StaticClass();
	PlayerStateClass = ARPGGamePlayerState::StaticClass();
	QuestClass = URPGGameQuestManager::StaticClass();
}

void ARPGGameGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	URPGCommonGameInstance* GameInstance = Cast<URPGCommonGameInstance>(GetGameInstance());
	GameInstance->CreateGameNPCData();
	GameInstance->CreateGameDataCopyClass();
	GameInstance->Init();

	//QuestManager �ʱ�ȭ
	_QuestManager = NewObject<URPGGameQuestManager>();

	//�� �ʱ�ȭ
	TArray<FString> MapName = { "Game_Village", "Desert" };
	{
		URPGGameMapInfo* NewVillageMap = NewObject<URPGGameVillageInfo>();
		NewVillageMap->SetMapName(MapName[0]);
		NewVillageMap->SetWorld(GetWorld());
		NewVillageMap->CreatePortal();
		_MapInfo.Add(NewVillageMap);
	}
	{
		URPGGameMapInfo* NewDesertMap = NewObject<URPGGameHuntMapInfo>();
		NewDesertMap->SetMapName(MapName[1]);
		NewDesertMap->SetWorld(GetWorld());
		NewDesertMap->CreatePortal();
		_MapInfo.Add(NewDesertMap);
	}



	TSharedPtr<FJsonObject> JsonObject2 = MakeShareable(new FJsonObject);
	JsonObject2->SetStringField("Name", GameInstance->GetCharacterName());
	GameInstance->PostRequest("/game/getquestinfo", JsonObject2);
}

void ARPGGameGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	URPGCommonGameInstance* GameInstance = Cast<URPGCommonGameInstance>(GetGameInstance());

	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	GameInstance->PostRequest("/users/logout", JsonObject);
	GameInstance->Release();
}

void ARPGGameGameMode::ActiveMap(const FString& MapName, ARPGGameCharacter* Character)
{
	FString CharacterCurrentMap = Character->GetCurrentMap();
	//ó�� �ʷε尡 �ƴҋ�
	if (CharacterCurrentMap.IsEmpty() == false)
	{
		FLatentActionInfo info;
		info.CallbackTarget = this;
		info.ExecutionFunction = FName("ExecutionUnLoad");
		info.UUID = 1;
		info.Linkage = 0;
		Character->SetCurrentMap(MapName);
		URPGGameMapInfo* Map = GetGameMap(CharacterCurrentMap);

		Map->SetHiddenGame(true);

		IRPGGameHuntMapInit* HuntInit = Cast<IRPGGameHuntMapInit>(Map);
		if (HuntInit != nullptr) HuntInit->SetHiddenEnemy(true);

		UGameplayStatics::UnloadStreamLevel(this, FName(*CharacterCurrentMap), info, true);
	}
	else //���� ���� �� �ʷε尡 ó���� ��
	{
		Character->SetCurrentMap(MapName);
		ExecutionUnLoad();
	}
}

void ARPGGameGameMode::StartPlay()
{
	Super::StartPlay();
}

void ARPGGameGameMode::ExecutionUnLoad()
{
	ARPGGameController* Controller = Cast<ARPGGameController>(GetWorld()->GetFirstPlayerController());
	ARPGGameCharacter* Character = Cast<ARPGGameCharacter>(Controller->GetPawn());

	FLatentActionInfo info;
	if (Character->GetNextMapPosition() != FVector::ZeroVector)
	{
		info.CallbackTarget = this;
		info.ExecutionFunction = FName("ExecutionLoad");
		info.UUID = 1;
		info.Linkage = 0;
	}

	UGameplayStatics::LoadStreamLevel(this, FName(*Character->GetCurrentMap()), true, true, info);

	URPGGameMapInfo* Map = GetGameMap(Character->GetCurrentMap());
	Map->SetHiddenGame(false);

	IRPGGameHuntMapInit* HuntInit = Cast<IRPGGameHuntMapInit>(Map);
	if (HuntInit != nullptr)
	{
		int CharacterLevel = Cast<ARPGGamePlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState)->GetCharacterLevel();
		HuntInit->Init(CharacterLevel, Character->GetActorLocation());
		HuntInit->SetHiddenEnemy(false);
	}
	
	UE_LOG(LogTemp, Warning, TEXT("ExecutionUnLoad"));
}

void ARPGGameGameMode::ExecutionLoad()
{
	ARPGGameController* Controller = Cast<ARPGGameController>(GetWorld()->GetFirstPlayerController());
	ARPGGameCharacter* Character = Cast<ARPGGameCharacter>(Controller->GetPawn());

	Character->SetActorLocation(Character->GetNextMapPosition());
	Controller->ComplateChangeMap();
}

void ARPGGameGameMode::AddNewNPC(TArray<FNPCInfo> NewNPC)
{
	ARPGGameController* Controller = Cast<ARPGGameController>(GetWorld()->GetFirstPlayerController());
	ARPGGameCharacter* Character = Cast<ARPGGameCharacter>(Controller->GetPawn());
	bool bActorHiddenInGmae = Character->GetCurrentMap() == "Desert";
	auto setInfo = [](ARPGGameNPC* NewGameNPC, FNPCInfo NewNPC, bool bHiddenActor) {
		NewGameNPC->SetInfo(NewNPC.SkeletalMesh, NewNPC.AnimInstanceClass, NewNPC.Position, NewNPC.Village, NewNPC.Name, NewNPC.Type, NewNPC.bQuest, NewNPC.Speech);
		NewGameNPC->SetActorHiddenInGame(bHiddenActor);
	};
	for (int i = 0; i < NewNPC.Num(); i++)
	{
		URPGGameMapInfo* MapInfo = GetGameMap(NewNPC[i].Village);
		if (NewNPC[i].bQuest == true)
		{
			ARPGGameNPCQuest* NewGameNPC = GetWorld()->SpawnActor<ARPGGameNPCQuest>(GameNPCQuestClass);
			setInfo(NewGameNPC, NewNPC[i], bActorHiddenInGmae);
			NewGameNPC->SetQuestList();
			MapInfo->AddNewNPC(NewGameNPC);
		}
		else
		{
			ARPGGameNPCShop* NewGameNPC = GetWorld()->SpawnActor<ARPGGameNPCShop>(GameNPCShopClass);
			setInfo(NewGameNPC, NewNPC[i], bActorHiddenInGmae);
			NewGameNPC->SetSpeech();
		
			MapInfo->AddNewNPC(NewGameNPC);
		}
	}
}

void ARPGGameGameMode::SetQuestInfo(const TArray<FRPGQuestInfo>& QuestInfo)
{
	_QuestManager->SetPreviousQuest(QuestInfo);
}

TArray<FRPGQuestInfo> ARPGGameGameMode::GetNPCNameToQuestInfo(const FString& Name)
{
	return _QuestManager->GetNPCNameToQuestInfo(Name);
}

URPGGameMapInfo* ARPGGameGameMode::GetGameMap(const FString& MapName)
{
	for (int i = 0; i < _MapInfo.Num(); i++)
	{
		if (_MapInfo[i]->GetMapName() == MapName)
			return _MapInfo[i];
	}
	return nullptr;
}
