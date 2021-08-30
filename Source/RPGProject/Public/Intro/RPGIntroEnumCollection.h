// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RPGIntroEnumCollection.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGIntroEnumCollection : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};

UENUM(BlueprintType)
enum class EIntroUIWidgetState : uint8
{

	Title = 0 UMETA(DisplayName = "Title"),
	Login = 1 UMETA(DisplayName = "Login"),
	Register = 2 UMETA(DisplayName = "Register"),
	Infor = 3 UMETA(DisplayName = "Infor"),
	NONE = 4 UMETA(DisplayName = "NONE")
};
