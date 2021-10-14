// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/RPGGamePlayerState.h"
#include "Game/RPGGameCharacterBagComponent.h"
#include "Common/RPGCommonGameInstance.h"
#include "Game/RPGGameDataTableManager.h"

ARPGGamePlayerState::ARPGGamePlayerState()
{
	_CharacterStat = MakeShareable(new FCharacterStat());

	_CharacterBagComponent = CreateDefaultSubobject<URPGGameCharacterBagComponent>(TEXT("BagComponent"));
}

void ARPGGamePlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	//_CharacterBagComponent->TestInfo();
}

void ARPGGamePlayerState::InitData(TArray<FRPGRestItem> RestItemData, const TMap<FString, FString>& MoneyData)
{
	_CharacterBagComponent->InitData(RestItemData, MoneyData);
}

void ARPGGamePlayerState::UsePortion(const TSharedPtr<FRPGItemInfo>& PortionInfo)
{
	if (_CharacterBagComponent->RemoveItem(PortionInfo->Name, 1) == false)
		return;
	URPGCommonGameInstance* GI = Cast<URPGCommonGameInstance>(GetWorld()->GetGameInstance());
	URPGGameDataTableManager* DTManager = GI->GetDataTableManager();
	FGameItemType* ItemType = DTManager->GetNameToData(PortionInfo->Name);
	for (int i = 0; i < ItemType->Property.Num(); i++)
	{
		int NewValue = _CharacterStat->Stat[ItemType->Property[i]] += ItemType->Stat[i];
		FString MaxString = "MAX"+ItemType->Property[i];
		int MaxValue = _CharacterStat->Stat[MaxString];
		_CharacterStat->Stat[ItemType->Property[i]] = FMath::Clamp(NewValue, 0, MaxValue);
	}
	_CharacterStat->TimeStamp++;
}

void ARPGGamePlayerState::AddExp(int Exp)
{
	int NewExp = _CharacterStat->Stat["EXP"] + Exp;
	if (NewExp > _CharacterStat->Stat["MAXEXP"])
	{
		int RestExp = NewExp - _CharacterStat->Stat["MAXEXP"];
		_CharacterStat->Stat["EXP"] = RestExp;
		LevelUp();
	}
	else
	{
		_CharacterStat->Stat["EXP"] += Exp;
	}
	_CharacterStat->TimeStamp++;
}

void ARPGGamePlayerState::LevelUp()
{
	_CharacterStat->Stat["STX"] += 5;
	_CharacterStat->Stat["MAXHP"] += 100;
	_CharacterStat->Stat["HP"] = _CharacterStat->Stat["MAXHP"];

	_CharacterStat->Stat["MAXMP"] += 50;
	_CharacterStat->Stat["MP"] = _CharacterStat->Stat["MAXMP"];
	_CharacterStat->Stat["LEVEL"]++;
}


