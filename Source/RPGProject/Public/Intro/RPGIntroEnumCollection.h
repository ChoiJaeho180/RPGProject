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
	MAIN = 0 UMETA(DisplayName = "Main"),
	LOBBY = 1 UMETA(DisplayName = "LOBBY"),
	CREATE = 2 UMETA(DisplayName = "Create"),
	NEXT_LEVEL = 3 UMETA (DisplayName = "NextLevel"),
	NONE = 4 UMETA (DisplayName = "None")
};

UENUM(BlueprintType)
enum class EIntroDerivedWidgetState : uint8
{
	MAIN_TITLE = 0 UMETA(DisplayName = "Title"),
	MAIN_LOGIN = 1 UMETA(DisplayName = "Login"),
	MAIN_REGISTER = 2 UMETA(DisplayName = "Register"),
	LOBBY_INFO = 3 UMETA(DisplayName = "Infor"),
	LOBBY_LOADING = 4 UMETA(DisplayName = "LOADING"),
	CREATE_CREATE = 5 UMETA(DisplayName = "Create"),
	CREATE_CUSTOM = 6 UMETA(DisplayName = "CUSTOM"),
	NONE = 7 UMETA(DisplayName = "NONE")
};
