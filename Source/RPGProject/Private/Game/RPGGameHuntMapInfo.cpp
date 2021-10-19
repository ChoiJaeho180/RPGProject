// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/RPGGameHuntMapInfo.h"
#include "Game/Enemy/RPGGameEnemyDog.h"
#include "Common/RPGCommonGameInstance.h"
#include "Game/RPGGameDataTableManager.h"
#include "Game/Enemy/RPGGameBaseAIController.h"
#include "Game/Animation/Enemy/RPGGameEnemyBaseAnim.h"
#include "Game/Enemy/RPGGameEnemyGriffon.h"
#include "Game/RPGGamePlayerState.h"

#define SPAWN_X_MIN -4000
#define SPAWN_X_MAX 4000

#define SPAWN_Y_MIN -1320
#define SPAWN_Y_MAX 3300

#define SPAWN_Z_VALUE 700

#define SPAWN_MAX_COUNT 10
#define SPAWN_CHARACTER_TO_ENEMY_DIST 1500

URPGGameHuntMapInfo::URPGGameHuntMapInfo()
{
	GameEnemyDogClass = ARPGGameEnemyDog::StaticClass();
	GameEnemyGriffonClass = ARPGGameEnemyGriffon::StaticClass();
}

void URPGGameHuntMapInfo::Init(int CharacterLevel, FVector CharacterLocation)
{
	int DogCount = FMath::Clamp(SPAWN_MAX_COUNT - CharacterLevel, 0, SPAWN_MAX_COUNT);

	int GriffonCount = FMath::Clamp(CharacterLevel, 1, SPAWN_MAX_COUNT);
	
	if (DogCount > _ActiveDogs.Num())
	{
		DogCount = DogCount - _ActiveDogs.Num();
		CreateEnemy(DogCount, EEnemyType::DOG, CharacterLocation, _ActiveDogs, _DisabledDogs);
	}
	if (GriffonCount > _ActiveGriffons.Num())
	{
		GriffonCount = GriffonCount - _ActiveGriffons.Num();
		CreateEnemy(GriffonCount, EEnemyType::GRIFFON, CharacterLocation, _ActiveGriffons, _DisabledGriffons);
	}

	//_bFirstInit = true;
}

void URPGGameHuntMapInfo::SetHiddenEnemy(bool bNewState)
{
	SetHiddenEnemyFactory(bNewState, _ActiveDogs);
	SetHiddenEnemyFactory(bNewState, _ActiveGriffons);
}

void URPGGameHuntMapInfo::SetHiddenEnemyFactory(bool bNewState, TArray<ARPGGameEnemyBase*>& ActiveEnemy)
{
	for (int i = 0; i < ActiveEnemy.Num(); i++)
	{
		ARPGGameBaseAIController* AIController = Cast<ARPGGameBaseAIController>(_ActiveDogs[i]->GetController());
		if (bNewState == true)
		{
			AIController->StopAI();
			ActiveEnemy[i]->GetCharacterMovement()->GravityScale = 0.0f;
		}
		else
		{
			if (ActiveEnemy[i]->GetEnemyBaseAnim()->GetDie() == true) continue;

			AIController->RunAI();
			ActiveEnemy[i]->GetCharacterMovement()->GravityScale = 1.0f;
		}
		ActiveEnemy[i]->SetActorHiddenInGame(bNewState);
	}
}

FVector URPGGameHuntMapInfo::GetSpawnPosition(FVector CharacterLocation)
{
	FVector EnemyLocation = FVector::ZeroVector;
	while (true)
	{
		EnemyLocation = FVector(FMath::RandRange(SPAWN_X_MIN, SPAWN_X_MAX), FMath::RandRange(SPAWN_Y_MIN, SPAWN_Y_MAX), SPAWN_Z_VALUE);
		if (FVector::Dist(EnemyLocation, CharacterLocation) > SPAWN_CHARACTER_TO_ENEMY_DIST)
			break;
	}
	return EnemyLocation;
}

void URPGGameHuntMapInfo::CreateEnemy(int Index, EEnemyType Type, FVector CharacterLocation, TArray<ARPGGameEnemyBase*>& ActiveEnemy, TArray<ARPGGameEnemyBase*>& DisabledEnemy )
{
	URPGCommonGameInstance* GameInstance = Cast<URPGCommonGameInstance>(_World->GetGameInstance());
	URPGGameDataTableManager* DataTableManager = GameInstance->GetDataTableManager();
	FGameEnemyInfo* TypeData = DataTableManager->GetEnemyTypeToData(Type);

	for (int i = 0; i < Index; i++)
	{
		auto InitEnemy = GetDisabledEnemy(DisabledEnemy);
		if (InitEnemy != nullptr)
		{
			ARPGGameBaseAIController* AIController = Cast<ARPGGameBaseAIController>(InitEnemy->GetController());
			AIController->RunAI();
			InitEnemy->GetCharacterMovement()->GravityScale = 1.0f;
			FVector Spawn = GetSpawnPosition(CharacterLocation);
			InitEnemy->SetActorLocation(Spawn);
			DisabledEnemy.Remove(InitEnemy);
			ActiveEnemy.Add(InitEnemy);
		}
		else
		{
			FVector Spawn = GetSpawnPosition(CharacterLocation);
			ARPGGameEnemyBase* Enemy = Type == EEnemyType::DOG ? SpawnDog(Spawn) : SpawnGriffon(Spawn);
			if (Enemy == nullptr) continue;
			Enemy->delegateOnDead.BindUObject(this, &URPGGameHuntMapInfo::UpdateDeadEnemy);
			Enemy->Init(TypeData->HP, TypeData->EnemyType, TypeData->Exp, TypeData->AverageDropGold, TypeData->BaseAttack);
			ActiveEnemy.Add(Enemy);
		}
	}
}

void URPGGameHuntMapInfo::UpdateDeadEnemy(ARPGGameEnemyBase* Enemy)
{
	EEnemyType EnemyType = Enemy->GetEnemyType();
	if (EnemyType == EEnemyType::DOG)
	{
		_ActiveDogs.Remove(Enemy);
		_DisabledDogs.Add(Enemy);
	}
	else
	{
		_ActiveGriffons.Remove(Enemy);
		_DisabledGriffons.Add(Enemy);
	}
	Enemy->SetActorHiddenInGame(true);
	Init(Cast<ARPGGamePlayerState>(_World->GetFirstPlayerController()->PlayerState)->GetCharacterLevel(), _World->GetFirstPlayerController()->GetPawn()->GetActorLocation());
}

ARPGGameEnemyBase* URPGGameHuntMapInfo::SpawnGriffon(FVector Location)
{
	return  _World->SpawnActor<ARPGGameEnemyGriffon>(GameEnemyGriffonClass, Location, FRotator());;
}

ARPGGameEnemyBase* URPGGameHuntMapInfo::SpawnDog(FVector Location)
{
	return _World->SpawnActor<ARPGGameEnemyDog>(GameEnemyDogClass, Location, FRotator());;
}

ARPGGameEnemyBase* URPGGameHuntMapInfo::GetDisabledEnemy(TArray<ARPGGameEnemyBase*> Enemys)
{
	ARPGGameEnemyBase* ReturnEnemy = nullptr;
	if (Enemys.Num() != 0)
	{
		ReturnEnemy = Enemys.Pop();
		ReturnEnemy->Response();
	}
	return ReturnEnemy;
}
