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
enum class EGameQuestNPCState : uint8
{
	READY,
	ING_YET,
	ING_COMPLATE,
	FINISH
};


UENUM(BlueprintType)
enum class ESkillState : uint8
{
	READY,
	ING,
	IMPOSSIBILITY
};

UENUM(BlueprintType)
enum class EGameMainUIType : uint8
{
	USER_LAYOUT,
	QUEST_LAYOUT
};

UENUM(BlueprintType)
enum class EInventoryUIType : uint8
{
	EQUIPMENT_INVENTORY,
	BAG_INVENTORY,
	STAT_INVENTORY,
	ETC_INVENTORY
};

UENUM(Blueprintable)
enum class EItemIsFrom : uint8
{
	None = 0,
	BAG = 1,
	Chest = 2,
	RIGHT_HOT_BAR = 3,
	LEFT_HOT_BAR = 4,
	EQUIP = 5,
	SHOP = 6
};

UENUM(BlueprintType)
enum class EInventoryType : uint8
{
	EQUIPMENT_INVENTORY,
	CONSUMPTION_INVENTORY,
	ETC_INVENTORY
};

UENUM(BlueprintType)
enum class EEnemyType : uint8
{
	DOG,
	GRIFFON
};


#define MIN_MOVE_DIST 150
#define PAWN_TO_POINT_DIST 120
#define NPC_TO_CHARACTER_DISTANCE 500
#define STARNDARD_TIME 0.025

#define PLUS_PERCENT_VALUE 0.008
#define STOP_LERP_VALUE 1
#define INIT_PERCENT_VALUE 0.0