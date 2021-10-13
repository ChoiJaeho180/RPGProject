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
		_MapInfo.Add(NewVillageMap);
	}
	{
		URPGGameMapInfo* NewDesertMap = NewObject<URPGGameHuntMapInfo>();
		_MapInfo.Add(NewDesertMap);
	}
	for(int i =0; i < MapName.Num(); i++)
	{
		_MapInfo[i]->SetMapName(MapName[i]);
		_MapInfo[i]->SetWorld(GetWorld());
		_MapInfo[i]->CreatePortal();
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
		UGameplayStatics::UnloadStreamLevel(this, FName(*CharacterCurrentMap), info, true);
	}
	else
	{
		Character->SetCurrentMap(MapName);
		ExecutionUnLoad();
	}
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
	
	URPGGameMapInfo* Map = GetGameMap(Character->GetCurrentMap());
	UGameplayStatics::LoadStreamLevel(this, FName(*Character->GetCurrentMap()), true, true, info);
	Map->SetHiddenGame(false);
	UE_LOG(LogTemp, Warning, TEXT("ExecutionUnLoad"));
}

void ARPGGameGameMode::ExecutionLoad()
{
	ARPGGameController* Controller = Cast<ARPGGameController>(GetWorld()->GetFirstPlayerController());
	ARPGGameCharacter* Character = Cast<ARPGGameCharacter>(Controller->GetPawn());
	//if (Character->GetNextMap() == FString("")) return;
	Character->SetActorLocation(Character->GetNextMapPosition());
	Controller->ComplateChangeMap();
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
