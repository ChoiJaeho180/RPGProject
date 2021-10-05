// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/RPGGameDataTableManager.h"
#include "Engine/DataTable.h"


URPGGameDataTableManager::URPGGameDataTableManager()
{
	FString ConsumptionPath = TEXT("DataTable'/Game/DataTable/ConsumptionItemType.ConsumptionItemType'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_CONSUMPTION(*ConsumptionPath);
	if (DT_CONSUMPTION.Succeeded())
	{
		_ConsumptionDT = DT_CONSUMPTION.Object;
	}
	
}

void URPGGameDataTableManager::Init()
{
	FString Context;
	_ConsumptionDT->GetAllRows<FGameItemType>(Context, _ConsumptionData);
}

void URPGGameDataTableManager::SetData(TArray<FGameItemType*> TargetData, UDataTable* TargetDT)
{
	FString Context;
	TargetDT->GetAllRows<FGameItemType>(Context, TargetData);
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

UTexture2D* URPGGameDataTableManager::GetNameToTexture(const FName& Name)
{
	for (int i = 0; i < _ConsumptionData.Num(); i++)
	{
		if (_ConsumptionData[i]->Name == Name)
			return _ConsumptionData[i]->Image;
	}
	return nullptr;
}
