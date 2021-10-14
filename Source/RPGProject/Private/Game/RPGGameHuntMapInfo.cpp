// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/RPGGameHuntMapInfo.h"
#include "Game/Enemy/RPGGameEnemyDog.h"
#include "Common/RPGCommonGameInstance.h"
#include "Game/RPGGameDataTableManager.h"

#define SPAWN_X_MIN -4000
#define SPAWN_X_MAX 4000

#define SPAWN_Y_MIN -3000
#define SPAWN_Y_MAX 3300

#define SPAWN_Z_VALUE 580

#define SPAWN_MAX_COUNT 20

URPGGameHuntMapInfo::URPGGameHuntMapInfo()
{
	GameEnemyDogClass = ARPGGameEnemyDog::StaticClass();
}

void URPGGameHuntMapInfo::Init()
{
	_bFirstInit = true;
	URPGCommonGameInstance* GameInstance = Cast<URPGCommonGameInstance>(_World->GetGameInstance());
	URPGGameDataTableManager* DataTableManager = GameInstance->GetDataTableManager();
	FGameEnemyInfo* TypeData = DataTableManager->GetEnemyTypeToData(EEnemyType::DOG);
	for (int i = 0; i < 10; i++)
	{
		FVector Spawn = GetSpawnPosition();
		ARPGGameEnemyDog* Dog = _World->SpawnActor<ARPGGameEnemyDog>(GameEnemyDogClass, Spawn, FRotator());
		if (Dog == nullptr)continue;
		Dog->Init(TypeData->HP, TypeData->EnemyType, TypeData->Exp, TypeData->AverageDropGold);
		_GameEnemyDogs.Add(Dog);
	}
}

FVector URPGGameHuntMapInfo::GetSpawnPosition()
{
	return FVector(FMath::RandRange(SPAWN_X_MIN, SPAWN_X_MAX), FMath::RandRange(SPAWN_Y_MIN, SPAWN_Y_MAX), SPAWN_Z_VALUE);
}
