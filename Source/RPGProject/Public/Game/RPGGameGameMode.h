// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include "Game/RPGGameQuestManager.h"
#include "Game/RPGGameNPCData.h"
#include "Game/RPGGameNPCShop.h"
#include "Game/RPGGameNPCQuest.h"
#include "GameFramework/GameMode.h"
#include "RPGGameGameMode.generated.h"

class URPGGameMapInfo;
class ARPGGameCharacter;
class URPGGameQuestManager;
class ARPGGameNPCQuest;
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
	UPROPERTY()
	URPGGameQuestManager* _QuestManager;
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
	void SetQuestInfo(const TArray<FRPGQuestInfo>& QuestInfo);
	TArray<FRPGQuestInfo> GetNPCNameToQuestInfo(const FString& Name);
	URPGGameMapInfo* GetGameMap(const FString& MapName);
	ARPGGameNPCQuest* GetQuest();
public:
	FORCEINLINE FString GetCantAttackMap() { return _CantAttackMap; }
public:
	TSubclassOf<URPGGameMapInfo> MapInfoClass;
	TSubclassOf<URPGGameQuestManager> QuestClass;
	TSubclassOf<ARPGGameNPC> GameNPCClass;
	TSubclassOf<ARPGGameNPCShop> GameNPCShopClass;
	TSubclassOf<ARPGGameNPCQuest> GameNPCQuestClass;

};
