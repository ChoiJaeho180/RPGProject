// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include "Game/RPGGameDataTable.h"
#include "UObject/NoExportTypes.h"
#include "RPGGameDataTableManager.generated.h"

class UDataTable;
class UTexture2D;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameDataTableManager : public UObject
{
	GENERATED_BODY()
private:
	UPROPERTY()
	UDataTable* _ConsumptionDT;
	TArray<FGameItemType*> _ConsumptionData;
	UPROPERTY()
	UDataTable* _PortalInfoDT;
	TArray<FPortalInfo*> _PortalData;

	UPROPERTY()
	UDataTable* _EnemyInfoDT;
	TArray<FGameEnemyInfo*> _EnemyData;

	UPROPERTY()
	UDataTable* _WarriorSkillDT;
	TArray<FGameSkillType*> _WarriorSkillData;

	UPROPERTY()
	UDataTable* _CharacterExpDT;
	TArray<FCharacterExp*> _CharacterExpData;
public:
	URPGGameDataTableManager();
	void Init();
private:
	void SetData(TArray<FGameItemType*> TargetData, UDataTable* TargetDT);
public:
	FCharacterExp* GetLevelToData(const int& Level);
	FGameSkillType* GetSkillNameToData(const FName& Name);
	FGameItemType* GetNameToData(const FName& Name);
	FGameEnemyInfo* GetEnemyTypeToData(const EEnemyType& Type);
	TArray<FPortalInfo*> GetPortalNameToData(const FString& Name);
	UTexture2D* GetNameToTexture(const FName& Name);
public:
	FORCEINLINE TArray<FGameItemType*> GetData() { return _ConsumptionData; }

};
