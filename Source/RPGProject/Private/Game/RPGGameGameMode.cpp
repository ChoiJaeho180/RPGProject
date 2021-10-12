// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/RPGGameGameMode.h"
#include "Game/RPGGameController.h"
#include "Game/RPGGameCharacter.h"
#include "Common/RPGCommonGameInstance.h"
#include "Game/RPGGameMapInfo.h"
#include "Game/RPGGamePlayerState.h"
#include "Common/REST/RPGCommonSerializeData.h"
#include "GameFramework/Controller.h"

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
	for(int i =0; i < MapName.Num(); i++)
	{
		URPGGameMapInfo* NewMap = NewObject<URPGGameMapInfo>();
		NewMap->SetMapName(MapName[i]);
		NewMap->CreatePortal(GetWorld());
		_MapInfo.Add(NewMap);
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

void ARPGGameGameMode::ActiveMap(const FString& MapName, ARPGGameCharacter* _Character)
{
	FLatentActionInfo info;
	FString CharacterCurrentMap = _Character->GetCurrentMap();
	if (CharacterCurrentMap.IsEmpty() == false)
	{
		URPGGameMapInfo* Map = GetGameMap(CharacterCurrentMap);
		Map->SetHiddenGame(true);
		UGameplayStatics::UnloadStreamLevel(this, FName(*CharacterCurrentMap), info, true);
	}
	_Character->SetCurrentMap(MapName);
	URPGGameMapInfo* Map = GetGameMap(_Character->GetCurrentMap());
	Map->SetHiddenGame(false);
	UGameplayStatics::LoadStreamLevel(this, FName(*_Character->GetCurrentMap()), true, true, info);
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
