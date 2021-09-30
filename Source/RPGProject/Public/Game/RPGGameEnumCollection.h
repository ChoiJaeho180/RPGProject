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
enum class EGameMapType : uint8
{
	VILLAGE,
	NONE
};

UENUM(BlueprintType)
enum class EGameMainUIType : uint8
{
	USER_LAYOUT,
	QUEST_LAYOUT
};

#define NPC_TO_CHARACTER_DISTANCE 500
#define STARNDARD_TIME 0.025

#define PLUS_PERCENT_VALUE 0.001
#define STOP_LERP_VALUE 1
#define INIT_PERCENT_VALUE 0.0