// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include "Game/RPGGameDataTable.h"
#include "UObject/NoExportTypes.h"
#include "RPGGameDataTableManager.generated.h"

class UDataTable;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameDataTableManager : public UObject
{
	GENERATED_BODY()
private:
	UDataTable* _ConsumptionDT;
	TArray<TSharedPtr<FGameItemType>> _ConsumptionData;
public:
	URPGGameDataTableManager();

private:
	void SetData(TArray<TSharedPtr<FGameItemType>>& TargetData, UDataTable* TargetDT);

};
