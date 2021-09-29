// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include "GameFramework/PlayerState.h"
#include "RPGGamePlayerState.generated.h"

USTRUCT(BlueprintType)
struct FCharacterStat
{
	GENERATED_BODY();
public:
	FCharacterStat() {};
	int Stx;
	int Dex;
	int Luk;
	int Int;
	int MaxHP;
	int CurrentHP;
	int MaxMP;
	int CurrentMP;
	int TimeStamp;
	
	void SetInfo(const TSharedPtr<FCharacterStat>& rhs)
	{
		Stx = rhs->Stx;
		Dex = rhs->Dex;
		Luk = rhs->Luk;
		Int = rhs->Int;
		MaxHP = rhs->MaxHP;
		CurrentHP = rhs->CurrentHP;
		MaxMP = rhs->MaxMP;
		CurrentMP = rhs->CurrentMP;
		TimeStamp = rhs->TimeStamp;
	}
	
};


/**
 * 
 */
UCLASS()
class RPGPROJECT_API ARPGGamePlayerState : public APlayerState
{
	GENERATED_BODY()
private:
	TSharedPtr<FCharacterStat> _CharacterStat;
public:
	ARPGGamePlayerState();

public:
	FORCEINLINE TSharedPtr<FCharacterStat>& GetCharacterStat() { return _CharacterStat; }
};
