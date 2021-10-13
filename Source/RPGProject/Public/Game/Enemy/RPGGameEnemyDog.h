// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Enemy/RPGGameEnemyBase.h"
#include "RPGGameEnemyDog.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJECT_API ARPGGameEnemyDog : public ARPGGameEnemyBase
{
	GENERATED_BODY()
	
public:
	ARPGGameEnemyDog();
	virtual void Init() override;
};
