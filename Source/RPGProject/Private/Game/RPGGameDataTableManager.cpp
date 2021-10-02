// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/RPGGameDataTableManager.h"
#include "Engine/DataTable.h"

URPGGameDataTableManager::URPGGameDataTableManager()
{
	FString ConsumptionPath = TEXT("DataTable'/Game/DataTable/ConsumptionItemType.ConsumptionItemType'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_CONSUMPTION(*ConsumptionPath);
	_ConsumptionDT = DT_CONSUMPTION.Object;
	SetData(_ConsumptionData, _ConsumptionDT);
	
	
}

void URPGGameDataTableManager::SetData(TArray<TSharedPtr<FGameItemType>>& TargetData, UDataTable* TargetDT)
{
	TArray<FGameItemType*> NewData;
	FString Context;
	TargetDT->GetAllRows<FGameItemType>(Context, NewData);
	for (int i = 0; i < NewData.Num(); i++)
	{
		TargetData.Add(MakeShareable(NewData[i]));
	}
}
