// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Skill/RPGGameBaseEffect.h"
#include "RPGGameAbilityR.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJECT_API ARPGGameAbilityR : public ARPGGameBaseEffect
{
	GENERATED_BODY()
private:
	float _CharacterMaxSpeed;
	float _RestoreMaxSpeed;
public:
	virtual void Init() override;
	virtual void ApplyProperty(ACharacter* pawn) override;
	virtual void RestoreProperty(ACharacter* pawn) override;
};
