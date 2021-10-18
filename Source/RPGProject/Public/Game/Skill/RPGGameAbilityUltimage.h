// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Skill/RPGGameBaseEffect.h"
#include "RPGGameAbilityUltimage.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJECT_API ARPGGameAbilityUltimage : public ARPGGameBaseEffect
{
	GENERATED_BODY()
public:
	virtual void ApplyProperty(ACharacter* pawn) override;
	virtual void Init() override;
};
