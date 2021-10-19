// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
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
	TArray<ARPGGameEnemyBase*> _ActiveDogs;
	TArray<ARPGGameEnemyBase*> _ActiveGriffons;

	TArray<ARPGGameEnemyBase*> _DisabledDogs;
	TArray<ARPGGameEnemyBase*> _DisabledGriffons;
public:
	URPGGameHuntMapInfo();
	virtual void Init(int CharacterLevel, FVector CharacterLocation) override;
	virtual void SetHiddenEnemy(bool bNewState) override;
	void SetHiddenEnemyFactory(bool bNewState, TArray<ARPGGameEnemyBase*>& ActiveEnemy);
	FVector GetSpawnPosition(FVector CharacterLocation);
	void CreateEnemy(int Index, EEnemyType Type, FVector CharacterLocation, TArray<ARPGGameEnemyBase*>& ActiveEnemy, TArray<ARPGGameEnemyBase*>& DisabledEnemy);
	void UpdateDeadEnemy(ARPGGameEnemyBase* Enemy);
	ARPGGameEnemyBase* SpawnGriffon(FVector Location);
	ARPGGameEnemyBase* SpawnDog(FVector Location);
private:
	ARPGGameEnemyBase* GetDisabledEnemy(TArray<ARPGGameEnemyBase*> Enemys);
public:
	TSubclassOf<ARPGGameEnemyDog> GameEnemyDogClass;
	TSubclassOf<ARPGGameEnemyGriffon> GameEnemyGriffonClass;
};
