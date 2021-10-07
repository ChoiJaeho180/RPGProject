// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include "Game/RPGGameItemStruct.h"
#include "GameFramework/PlayerState.h"
#include "RPGGamePlayerState.generated.h"

class URPGGameCharacterBagComponent;

USTRUCT(BlueprintType)
struct FCharacterStat
{
	GENERATED_BODY();
public:
	TMap<FString, int> Stat;
	int TimeStamp;
	FCharacterStat()
	{
		Stat.Add("LEVEL", 1);
		Stat.Add("MAXEXP", 100);
		Stat.Add("EXP", 0);
		Stat.Add("STX", 10);
		Stat.Add("INT", 10);
		Stat.Add("DEX", 10);
		Stat.Add("LUK", 10);
		Stat.Add("SPECIALSTATE", 0);
		Stat.Add("MAXHP", 100);
		Stat.Add("HP", 100);
		Stat.Add("MAXMP", 100);
		Stat.Add("MP", 75);
	}
	void SetInfo(const TSharedPtr<FCharacterStat>& rhs)
	{
		Stat = rhs->Stat;
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
	virtual void PostInitializeComponents() override;
	void InitData(TArray<FRPGRestItem> RestItemData);
	void UsePortion(const TSharedPtr<FRPGItemInfo>& PortionInfo);
public:
	FORCEINLINE TSharedPtr<FCharacterStat>& GetCharacterStat() { return _CharacterStat; }
	FORCEINLINE URPGGameCharacterBagComponent* GetCharacterBag() { return _CharacterBagComponent; }

};
