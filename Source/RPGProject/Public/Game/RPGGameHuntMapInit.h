// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RPGGameHuntMapInit.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URPGGameHuntMapInit : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RPGPROJECT_API IRPGGameHuntMapInit
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	bool _bFirstInit;
	virtual void Init() = 0;
	virtual void SetHiddenEnemy(bool bNewState) = 0;
};
