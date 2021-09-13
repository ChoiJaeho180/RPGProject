// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Intro/UI/RPGIntroLobbySlotInfoLayout.h"
#include "Intro/UI/RPGIntroLobbySlotInfo.h"
#include "Intro/UI/RPGIntroBaseLayout.h"
#include "RPGIntroLobbyInfoLayout.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGIntroLobbyInfoLayout : public URPGIntroBaseLayout, public IRPGIntroLobbySlotInfo
{
	GENERATED_BODY()
private:
	UPROPERTY()
	TArray<URPGIntroLobbySlotInfoLayout*> _CharacterSlotInfo;
public:

	virtual void NativeConstruct() override;
	virtual void SetSlotInfo() override;
};
