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
}

void ARPGGameGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	URPGCommonGameInstance* GameInstance = Cast<URPGCommonGameInstance>(GetGameInstance());
	GameInstance->CreateGameNPCData();
	GameInstance->CreateGameDataCopyClass();
	GameInstance->Init();
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

	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	GameInstance->PostRequest("/game/getnpcinfo", JsonObject);
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
	//처음 맵로드가 아닐떄
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
	else //게임 시작 후 맵로드가 처음일 때
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
		HuntInit->Init();
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
	UE_LOG(LogTemp, Warning, TEXT("%f, %f, %f"), Character->GetNextMapPosition().X, Character->GetNextMapPosition().Y, Character->GetNextMapPosition().Z);
	UE_LOG(LogTemp, Warning, TEXT("??"));
}

void ARPGGameGameMode::AddNewNPC(TArray<FNPCInfo> NewNPC)
{
	auto setInfo = [](ARPGGameNPC* NewGameNPC, FNPCInfo NewNPC) {
		NewGameNPC->SetInfo(NewNPC.SkeletalMesh, NewNPC.AnimInstanceClass, NewNPC.Position, NewNPC.Village, NewNPC.Name, NewNPC.Type, NewNPC.bQuest, NewNPC.Speech);
		NewGameNPC->SetActorHiddenInGame(true);
	};

	for (int i = 0; i < NewNPC.Num(); i++)
	{
		URPGGameMapInfo* MapInfo = GetGameMap(NewNPC[i].Village);
		if (NewNPC[i].bQuest == true)
		{
			ARPGGameNPCQuest* NewGameNPC = GetWorld()->SpawnActor<ARPGGameNPCQuest>(GameNPCQuestClass);
			setInfo(NewGameNPC, NewNPC[i]);
			_MapInfo[i]->AddNewNPC(NewGameNPC);
		}
		else
		{
			ARPGGameNPCShop* NewGameNPC = GetWorld()->SpawnActor<ARPGGameNPCShop>(GameNPCShopClass);
			setInfo(NewGameNPC, NewNPC[i]);
			NewGameNPC->SetSpeech();
			_MapInfo[i]->AddNewNPC(NewGameNPC);
		}
	}
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
