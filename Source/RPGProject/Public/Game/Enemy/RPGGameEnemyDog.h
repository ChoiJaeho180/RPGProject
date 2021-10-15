// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Enemy/RPGGameEnemyBase.h"
#include "RPGGameEnemyDog.generated.h"

class URPGGameDogAnim;

/**
 * 
 */
UCLASS()
class RPGPROJECT_API ARPGGameEnemyDog : public ARPGGameEnemyBase
{
	GENERATED_BODY()
private:
	
public:
	ARPGGameEnemyDog();
	virtual void BeginPlay() override;
};
