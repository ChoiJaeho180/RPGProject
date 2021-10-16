// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/RPGGameHuntMapInit.h"
#include "Game/RPGGameMapInfo.h"
#include "RPGGameHuntMapInfo.generated.h"

class ARPGGameEnemyDog;
class ARPGGameEnemyGriffon;
class ARPGGameEnemyBase;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameHuntMapInfo : public URPGGameMapInfo, public IRPGGameHuntMapInit
{
	GENERATED_BODY()
private:
	TArray<ARPGGameEnemyBase*> _GameEnemyDogs;
public:
	URPGGameHuntMapInfo();
	virtual void Init() override;
	virtual void SetHiddenEnemy(bool bNewState) override;
	FVector GetSpawnPosition();
public:
	TSubclassOf<ARPGGameEnemyDog> GameEnemyDogClass;
	TSubclassOf<ARPGGameEnemyGriffon> GameEnemyGriffonClass;
};
