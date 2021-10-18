// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/RPGGameDataTableManager.h"
#include "Engine/DataTable.h"


URPGGameDataTableManager::URPGGameDataTableManager()
{
	FString ConsumptionPath = TEXT("DataTable'/Game/DataTable/ConsumptionPortionType.ConsumptionPortionType'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_CONSUMPTION(*ConsumptionPath);
	if (DT_CONSUMPTION.Succeeded())
	{
		_ConsumptionDT = DT_CONSUMPTION.Object;
	}
	FString PorTalInfoPath = TEXT("DataTable'/Game/DataTable/PorTalInfo.PorTalInfo'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_PORTALINFO(*PorTalInfoPath);
	if (DT_PORTALINFO.Succeeded())
	{
		_PortalInfoDT = DT_PORTALINFO.Object;
	}
	FString EnemyInfoPath = TEXT("DataTable'/Game/DataTable/EnemyInfo.EnemyInfo'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ENEMYINFO(*EnemyInfoPath);
	if (DT_ENEMYINFO.Succeeded())
	{
		_EnemyInfoDT = DT_ENEMYINFO.Object;
	}
	FString WarriorSkillTypePath = TEXT("DataTable'/Game/DataTable/WarriorSkillType.WarriorSkillType'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_WARRIOR_SKILL_INFO(*WarriorSkillTypePath);
	if (DT_WARRIOR_SKILL_INFO.Succeeded())
	{
		_WarriorSkillDT = DT_WARRIOR_SKILL_INFO.Object;
	}
}

void URPGGameDataTableManager::Init()
{
	FString Context;
	_ConsumptionDT->GetAllRows<FGameItemType>(Context, _ConsumptionData);
	_PortalInfoDT->GetAllRows<FPortalInfo>(Context, _PortalData);
	_EnemyInfoDT->GetAllRows<FGameEnemyInfo>(Context, _EnemyData);
	_WarriorSkillDT->GetAllRows<FGameSkillType>(Context, _WarriorSkillData);
}

void URPGGameDataTableManager::SetData(TArray<FGameItemType*> TargetData, UDataTable* TargetDT)
{
	FString Context;
	TargetDT->GetAllRows<FGameItemType>(Context, TargetData);
}

FGameSkillType* URPGGameDataTableManager::GetSkillNameToData(const FName& Name)
{
	for (int i = 0; i < _WarriorSkillData.Num(); i++)
	{
		if (_WarriorSkillData[i]->Name == Name)
			return _WarriorSkillData[i];
	}
	return nullptr;
}

FGameItemType* URPGGameDataTableManager::GetNameToData(const FName& Name)
{
	for (int i = 0; i < _ConsumptionData.Num(); i++)
	{
		if (_ConsumptionData[i]->Name == Name)
			return _ConsumptionData[i];
	}
	return nullptr;
}

FGameEnemyInfo* URPGGameDataTableManager::GetEnemyTypeToData(const EEnemyType& Type)
{
	for (int i = 0; i < _ConsumptionData.Num(); i++)
	{
		if (_EnemyData[i]->EnemyType == Type)
			return _EnemyData[i];
	}
	return nullptr;
}

TArray<FPortalInfo*> URPGGameDataTableManager::GetPortalNameToData(const FString& Name)
{
	TArray<FPortalInfo*> Data;
	for (int i = 0; i < _PortalData.Num(); i++)
	{
		if (_PortalData[i]->CurrentMap == Name)
			Data.Add(_PortalData[i]);
	}
	return Data;
}

UTexture2D* URPGGameDataTableManager::GetNameToTexture(const FName& Name)
{
	for (int i = 0; i < _ConsumptionData.Num(); i++)
	{
		if (_ConsumptionData[i]->Name == Name)
			return _ConsumptionData[i]->Image;
	}
	return nullptr;
}
