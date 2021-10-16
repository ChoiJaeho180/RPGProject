// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Enemy/RPGGameEnemyBase.h"
#include "RPGGameEnemyGriffon.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJECT_API ARPGGameEnemyGriffon : public ARPGGameEnemyBase
{
	GENERATED_BODY()

public:
	ARPGGameEnemyGriffon();
	virtual void BeginPlay() override;
	
};
