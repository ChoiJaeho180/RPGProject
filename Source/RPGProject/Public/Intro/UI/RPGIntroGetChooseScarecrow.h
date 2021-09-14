// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RPGIntroGetChooseScarecrow.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URPGIntroGetChooseScarecrow : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RPGPROJECT_API IRPGIntroGetChooseScarecrow
{
	GENERATED_BODY()
protected:
	FString _CharacterName;
	int _ScarecrowIndex;
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SetCharacterName(const FString& NewName) = 0;
	virtual FString GetCharacterName() = 0 ;
	virtual void SetScarecrowIndex(const int& NewName) = 0;
	virtual int GetScarecrowIndex() = 0;
};
