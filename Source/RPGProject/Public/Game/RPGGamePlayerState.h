// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include "GameFramework/PlayerState.h"
#include "RPGGamePlayerState.generated.h"

class URPGGameCharacterBagComponent;

USTRUCT(BlueprintType)
struct FCharacterStat
{
	GENERATED_BODY();
public:
	FCharacterStat() {};
	int Level;
	int MaxExp;
	int CurrentExp;
	int Stx;
	int Dex;
	int Luk;
	int Int;
	int SpecialState;
	int MaxHP = 100;
	int CurrentHP = 100;
	int MaxMP = 100;
	int CurrentMP = 75;
	int TimeStamp;

	void SetInfo(const TSharedPtr<FCharacterStat>& rhs)
	{
		Level = rhs->Level;
		MaxExp = rhs->MaxExp;
		CurrentExp = rhs->CurrentExp;
		Stx = rhs->Stx;
		Dex = rhs->Dex;
		Luk = rhs->Luk;
		Int = rhs->Int;
		MaxHP = rhs->MaxHP;
		CurrentHP = rhs->CurrentHP;
		MaxMP = rhs->MaxMP;
		CurrentMP = rhs->CurrentMP;
		TimeStamp = rhs->TimeStamp;
		SpecialState = rhs->SpecialState;
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
	UPROPERTY()
	URPGGameCharacterBagComponent* _CharacterBagComponent;
public:
	ARPGGamePlayerState();

public:
	FORCEINLINE TSharedPtr<FCharacterStat>& GetCharacterStat() { return _CharacterStat; }
};
