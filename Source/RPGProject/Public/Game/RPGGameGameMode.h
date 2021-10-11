// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include "Game/RPGGameNPCData.h"
#include "Game/RPGGameNPCShop.h"
#include "Game/RPGGameNPCQuest.h"
#include "GameFramework/GameMode.h"
#include "RPGGameGameMode.generated.h"

class URPGGameMapInfo;

/**
 * 
 */
UCLASS()
class RPGPROJECT_API ARPGGameGameMode : public AGameMode
{
	GENERATED_BODY()
private:
	UPROPERTY()
	TArray<URPGGameMapInfo*> _MapInfo;
	FString _CurrentMapName;
public:
	ARPGGameGameMode();

	void PostLogin(APlayerController* NewPlayer);
	void Logout(AController* Exiting);
	void ActiveMap(const FString& MapName);
	void AddNewNPC(TArray<FNPCInfo> NewNPC);
	URPGGameMapInfo* GetGameMap(const FString& MapName);
public:
	FORCEINLINE FString GetCurrentMap() { return _CurrentMapName; }
public:
	TSubclassOf<URPGGameMapInfo> MapInfoClass;
	TSubclassOf<ARPGGameNPC> GameNPCClass;
	TSubclassOf<ARPGGameNPCShop> GameNPCShopClass;
	TSubclassOf<ARPGGameNPCQuest> GameNPCQuestClass;

};
