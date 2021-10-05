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
	UDataTable* _ConsumptionDT;
	TArray<FGameItemType*> _ConsumptionData;
public:
	URPGGameDataTableManager();
	void Init();
private:
	void SetData(TArray<FGameItemType*> TargetData, UDataTable* TargetDT);
public:
	FGameItemType* GetNameToData(const FName& Name);
	UTexture2D* GetNameToTexture(const FName& Name);
public:
	FORCEINLINE TArray<FGameItemType*> GetData() { return _ConsumptionData; }
};
