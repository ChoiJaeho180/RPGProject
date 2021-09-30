// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Game/UI/RPGGameBaseLayout.h"
#include "RPGGameActionBarLayout.generated.h"

class URPGGameActionBarSlot;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameActionBarLayout : public URPGGameBaseLayout
{
	GENERATED_BODY()
private:
	UPROPERTY()
	TArray<URPGGameActionBarSlot*> _ActionBarSlots;
public:
	virtual void NativeConstruct() override;
	
};
