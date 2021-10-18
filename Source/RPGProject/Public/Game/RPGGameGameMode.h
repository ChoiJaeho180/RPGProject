// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include "Game/RPGGameNPCData.h"
#include "Game/RPGGameNPCShop.h"
#include "Game/RPGGameNPCQuest.h"
#include "GameFramework/GameMode.h"
#include "RPGGameGameMode.generated.h"

class URPGGameMapInfo;
class ARPGGameCharacter;
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
	const FString _CantAttackMap = "Game_Village";
public:
	ARPGGameGameMode();

	void PostLogin(APlayerController* NewPlayer);
	void Logout(AController* Exiting);
	void ActiveMap(const FString& MapName, ARPGGameCharacter* _Character);
	virtual void StartPlay() override;
	UFUNCTION()
	void ExecutionUnLoad();
	UFUNCTION()
	void ExecutionLoad();
	void AddNewNPC(TArray<FNPCInfo> NewNPC);
	URPGGameMapInfo* GetGameMap(const FString& MapName);
public:
	FORCEINLINE FString GetCantAttackMap() { return _CantAttackMap; }
public:
	TSubclassOf<URPGGameMapInfo> MapInfoClass;
	TSubclassOf<ARPGGameNPC> GameNPCClass;
	TSubclassOf<ARPGGameNPCShop> GameNPCShopClass;
	TSubclassOf<ARPGGameNPCQuest> GameNPCQuestClass;

};
