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
	CREATE = 2 UMETA(DisplayName = "Create")
};

UENUM(BlueprintType)
enum class EIntroDerivedWidgetState : uint8
{
	MAIN_TITLE = 0 UMETA(DisplayName = "Title"),
	MAIN_LOGIN = 1 UMETA(DisplayName = "Login"),
	MAIN_REGISTER = 2 UMETA(DisplayName = "Register"),
	LOBBY_INFO = 3 UMETA(DisplayName = "Infor"),
	CREATE_CREATE = 4 UMETA(DisplayName = "Create"),
	CREATE_CUSTOM = 5 UMETA(DisplayName = "CUSTOM"),
	TO_LOBBY = 6 UMETA(DisplayName = "ToSelect"),
	TO_CREATE = 7 UMETA(DisplayName = "ToCreate"),
	TO_MAIN = 8 UMETA(DisplayName = "ToMain"),
	NONE = 9 UMETA(DisplayName = "NONE")
};
