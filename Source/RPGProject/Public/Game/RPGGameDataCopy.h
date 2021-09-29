// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/RPGGamePlayerState.h"
#include "GameFramework/Actor.h"
#include "RPGGameDataCopy.generated.h"

class ARPGGamePlayerState;

UCLASS()
class RPGPROJECT_API ARPGGameDataCopy : public AActor
{
	GENERATED_BODY()
private:
	TSharedPtr<FCharacterStat> _CharacterStat;
	ARPGGamePlayerState* _CheckStat;
	float _DeltaTime;
public:	
	// Sets default values for this actor's properties
	ARPGGameDataCopy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void CheckCharacterStat();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
