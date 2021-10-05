// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include "Game/RPGGamePlayerState.h"
#include "Game/RPGGameItemStruct.h"
#include "GameFramework/Actor.h"
#include "RPGGameDataCopy.generated.h"

class ARPGGamePlayerState;

UCLASS()
class RPGPROJECT_API ARPGGameDataCopy : public AActor
{
	GENERATED_BODY()
private:
	TSharedPtr<FCharacterStat> _CharacterStat;
	TArray<TSharedPtr<FRPGItemInfo>> _CharacterItemInfo;
	ARPGGamePlayerState* _CheckStat;
	float _DeltaTime;
public:	
	// Sets default values for this actor's properties
	ARPGGameDataCopy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void CheckCharacterStat();
	void CheckCharacterItems();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	FORCEINLINE TSharedPtr<FCharacterStat>& GetCharacterStat() { return _CharacterStat; }
	FORCEINLINE TArray<TSharedPtr<FRPGItemInfo>> GetCharacterItemsInfo() { return _CharacterItemInfo; }
};
