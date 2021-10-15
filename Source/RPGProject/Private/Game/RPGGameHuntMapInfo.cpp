// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/RPGGameHuntMapInfo.h"
#include "Game/Enemy/RPGGameEnemyDog.h"
#include "Common/RPGCommonGameInstance.h"
#include "Game/RPGGameDataTableManager.h"
#include "Game/Enemy/RPGGameBaseAIController.h"

#define SPAWN_X_MIN -4000
#define SPAWN_X_MAX 4000

#define SPAWN_Y_MIN -1320
#define SPAWN_Y_MAX 3300

#define SPAWN_Z_VALUE 700

#define SPAWN_MAX_COUNT 20

URPGGameHuntMapInfo::URPGGameHuntMapInfo()
{
	GameEnemyDogClass = ARPGGameEnemyDog::StaticClass();
}

void URPGGameHuntMapInfo::Init()
{
	if (_bFirstInit == true) return;

	URPGCommonGameInstance* GameInstance = Cast<URPGCommonGameInstance>(_World->GetGameInstance());
	URPGGameDataTableManager* DataTableManager = GameInstance->GetDataTableManager();
	FGameEnemyInfo* TypeData = DataTableManager->GetEnemyTypeToData(EEnemyType::DOG);
	for (int i = 0; i < 10; i++)
	{
		FVector Spawn = GetSpawnPosition();
		ARPGGameEnemyDog* Dog = _World->SpawnActor<ARPGGameEnemyDog>(GameEnemyDogClass, Spawn, FRotator());
		if (Dog == nullptr)continue;
		Dog->Init(TypeData->HP, TypeData->EnemyType, TypeData->Exp, TypeData->AverageDropGold, TypeData->BaseAttack);
		_GameEnemyDogs.Add(Dog);
	}
	_bFirstInit = true;
}

void URPGGameHuntMapInfo::SetHiddenEnemy(bool bNewState)
{
	for (int i = 0; i < _GameEnemyDogs.Num(); i++)
	{
		ARPGGameBaseAIController* AIController = Cast<ARPGGameBaseAIController>(_GameEnemyDogs[i]->GetController());
		if (bNewState == true)
		{
			AIController->StopAI();
			_GameEnemyDogs[i]->GetCharacterMovement()->GravityScale = 0.0f;
		}
		else
		{
			AIController->RunAI();
			_GameEnemyDogs[i]->GetCharacterMovement()->GravityScale = 1.0f;
		}
		_GameEnemyDogs[i]->SetActorHiddenInGame(bNewState);
	}
}

FVector URPGGameHuntMapInfo::GetSpawnPosition()
{
	return FVector(FMath::RandRange(SPAWN_X_MIN, SPAWN_X_MAX), FMath::RandRange(SPAWN_Y_MIN, SPAWN_Y_MAX), SPAWN_Z_VALUE);
}
