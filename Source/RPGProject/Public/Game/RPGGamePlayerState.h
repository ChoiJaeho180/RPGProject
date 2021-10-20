// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include "Game/RPGGameItemStruct.h"
#include "GameFramework/PlayerState.h"
#include "RPGGamePlayerState.generated.h"

class URPGGameCharacterBagComponent;

DECLARE_DELEGATE(FOnReadySpecialBarDelegate);
DECLARE_DELEGATE(FOnLevelUpDelegate);
USTRUCT(BlueprintType)
struct FCharacterStat
{
	GENERATED_BODY();
public:
	TMap<FString, int> Stat;
	int TimeStamp = 0;
	FCharacterStat()
	{
		Stat.Add("LEVEL", 1000);
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
		TimeStamp++;
	}
	void SetInfo(const TMap<FString, FString>& NewStat)
	{
		Stat["LEVEL"] = FCString::Atoi(*NewStat["LEVEL"]);
		Stat["MAXEXP"] = FCString::Atoi(*NewStat["MAXEXP"]);
		Stat["EXP"] = FCString::Atoi(*NewStat["EXP"]);
		Stat["STX"] = FCString::Atoi(*NewStat["STX"]);
		Stat["INT"] = FCString::Atoi(*NewStat["INT"]);
		Stat["DEX"] = FCString::Atoi(*NewStat["DEX"]);
		Stat["LUK"] = FCString::Atoi(*NewStat["LUK"]);
		Stat["SPECIALSTATE"] = FCString::Atoi(*NewStat["SPECIALSTATE"]);
		Stat["MAXHP"] = FCString::Atoi(*NewStat["MAXHP"]);
		Stat["HP"] = FCString::Atoi(*NewStat["HP"]);
		Stat["MAXMP"] = FCString::Atoi(*NewStat["MAXMP"]);
		Stat["MP"] = FCString::Atoi(*NewStat["MP"]);
		TimeStamp++;
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
	
	TArray<int> _AddExpLog;
public:
	ARPGGamePlayerState();
	virtual void PostInitializeComponents() override;
	void InitData(TArray<FRPGRestItem> RestItemData, const TMap<FString, FString>& MoneyData);
	void UsePortion(const TSharedPtr<FRPGItemInfo>& PortionInfo);
	void AddHP(int AddHP = 99999);
	void AddMP(int AddMP = 99999);
	void AddGold(int Gold, bool bAddLog);
	void AddExp(int Exp, bool bAddLog);
	void AddSpecialBar(int AddRatio);
	void LevelUp();

	TSharedPtr<FRPGItemInfo> GetFindItem(const FName& Name);

public:
	FOnReadySpecialBarDelegate delegateReadySpecialBar;
	FOnLevelUpDelegate delegateLevelUp;
public:
	FORCEINLINE TArray<int> GetAddExpLog() { return _AddExpLog; }
	FORCEINLINE void RemoveAddExpLog() { _AddExpLog.Empty(); }
	FORCEINLINE TSharedPtr<FCharacterStat>& GetCharacterStat() { return _CharacterStat; }
	FORCEINLINE URPGGameCharacterBagComponent* GetCharacterBag() { return _CharacterBagComponent; }
	FORCEINLINE int GetCharacterHP() { return _CharacterStat->Stat["HP"]; }
	
	FORCEINLINE int GetCharacterLevel() { return _CharacterStat->Stat["LEVEL"]; }
	FORCEINLINE int GetCharacterMP() { return _CharacterStat->Stat["MP"]; }
	FORCEINLINE int GetSpecialBar() { return _CharacterStat->Stat["SPECIALSTATE"]; }
};
