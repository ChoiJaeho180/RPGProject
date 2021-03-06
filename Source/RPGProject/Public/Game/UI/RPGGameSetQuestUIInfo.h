// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Game/RPGGameQuestManager.h"
#include "UObject/Interface.h"
#include "RPGGameSetQuestUIInfo.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URPGGameSetQuestUIInfo : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RPGPROJECT_API IRPGGameSetQuestUIInfo
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	FOnChangeQuestToMainWidgetDelegate delegateChangeQuestToMainWidget;
	virtual void SetQuestInfo(const FRPGQuestInfo& QuestInfo, EGameQuestNPCState State) = 0;
};
