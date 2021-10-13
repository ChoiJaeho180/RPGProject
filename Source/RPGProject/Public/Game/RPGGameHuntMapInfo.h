// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/RPGGameMapInfo.h"
#include "RPGGameHuntMapInfo.generated.h"

class ARPGGameEnemyDog;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameHuntMapInfo : public URPGGameMapInfo
{
	GENERATED_BODY()
private:
	TArray<ARPGGameEnemyDog*> _GameEnemyDogs;
public:
	URPGGameHuntMapInfo();
public:
	TSubclassOf<ARPGGameEnemyDog> GameEnemyDogClass;
};
