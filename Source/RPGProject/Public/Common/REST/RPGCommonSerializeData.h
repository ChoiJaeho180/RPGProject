// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/RPGGameItemStruct.h"
#include "UObject/NoExportTypes.h"
#include "RPGCommonSerializeData.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGCommonSerializeData : public UObject
{
	GENERATED_BODY()
	
public:
	static FString GetCharacterStat(TMap<FString, int> CharacterStat);
	static FString GetMoney(int Money);
	static FString GetItemsData(const TArray<TSharedPtr<FRPGItemSlot>>& ItemsData);
	static FString GetLastPosition(const FString& Village, const FVector& Position);
};
