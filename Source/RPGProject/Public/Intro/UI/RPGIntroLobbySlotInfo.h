// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dom/JsonValue.h"
#include "UObject/Interface.h"
#include "RPGIntroLobbySlotInfo.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URPGIntroLobbySlotInfo : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RPGPROJECT_API IRPGIntroLobbySlotInfo
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	TArray<TSharedPtr<FJsonValue>> Info;
	virtual void SetSlotInfo() = 0;
};
