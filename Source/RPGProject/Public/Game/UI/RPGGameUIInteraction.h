// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/RPGGameDataCopy.h"
#include "UObject/Interface.h"
#include "RPGGameUIInteraction.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URPGGameUIInteraction : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RPGPROJECT_API IRPGGameUIInteraction
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	ARPGGameDataCopy* GameDataCopy;
	float InteractionDeltaTime;
	virtual void SetGameDataCopy()=0;
	virtual void UpdateProperty() = 0;
};
