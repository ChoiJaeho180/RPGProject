// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RPGCommonEnumCollection.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGCommonEnumCollection : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};

UENUM(BlueprintType)
enum class ECommonFadeState : uint8
{
	FADE_IN = 0 UMETA(DisplayName = "FADE_IN"),
	FADE_OUT = 1 UMETA(DisplayName = "FADE_OUT"),
	NONE = 2 UMETA(DisplayName = "NONE")
};

UENUM(BlueprintType)
enum class ECommonJob : uint8
{
	WARRIOR = 0 UMETA(DisplayName = "WARRIOR"),
	NONE = 2 UMETA(DisplayName = "NONE")
};

#define SUCCESSD_REST_API "0"