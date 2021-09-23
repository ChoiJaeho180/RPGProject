// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RPGGameEnumCollection.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameEnumCollection : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};

UENUM(BlueprintType)
enum class EGameTownNPCType : uint8
{
	SHOP_NPC,
	QUEST_NPC,
	NONE
};

UENUM(BlueprintType)
enum class EGameMapType : uint8
{
	VILLAGE,
	NONE
};
