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

void ARPGGamePlayerState::AddHP(int AddHP)
{
	int resultHP = FMath::Clamp(_CharacterStat->Stat["HP"] + AddHP, 0, _CharacterStat->Stat["MAXHP"]);
	_CharacterStat->Stat["HP"] = resultHP;
	_CharacterStat->TimeStamp++;
}

void ARPGGamePlayerState::AddMP(int AddMP)
{
	int resultMP = FMath::Clamp(_CharacterStat->Stat["MP"] + AddMP, 0, _CharacterStat->Stat["MAXMP"]);
	_CharacterStat->Stat["MP"] = resultMP;
	_CharacterStat->TimeStamp++;
}

void ARPGGamePlayerState::AddGold(int Gold, bool bAddLog)
{
	_CharacterBagComponent->UpdateMoney(Gold, bAddLog);
}

void ARPGGamePlayerState::AddSpecialBar(int AddRatio)
{
	_CharacterStat->Stat["SPECIALSTATE"] = FMath::Clamp(_CharacterStat->Stat["SPECIALSTATE"] + AddRatio, 0, 100);
	_CharacterStat->TimeStamp++;
	if (_CharacterStat->Stat["SPECIALSTATE"] >= 100)
	{
		UE_LOG(LogTemp, Warning, TEXT("delegateReadySpecialBar"));
		delegateReadySpecialBar.ExecuteIfBound();
	}
	UE_LOG(LogTemp, Warning, TEXT("%d"), _CharacterStat->Stat["SPECIALSTATE"]);
	
}

void ARPGGamePlayerState::AddExp(int Exp, bool bAddLog)
{
	if (bAddLog) _AddExpLog.Add(Exp);

	int NewExp = _CharacterStat->Stat["EXP"] + Exp;
	if (NewExp >= _CharacterStat->Stat["MAXEXP"])
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

void ARPGGamePlayerState::AddState(FString StatName, int Value)
{
	if (StatName == "EXP") AddExp(Value, false);
	else if (StatName == "Money") AddGold(Value, false);
	else
	{
		URPGCommonGameInstance* GI = Cast<URPGCommonGameInstance>(GetWorld()->GetGameInstance());
		URPGGameDataTableManager* DTManager = GI->GetDataTableManager();
		FGameItemType* ItemType = DTManager->GetNameToData(FName(*StatName));
		TSharedPtr<FRPGItemInfo> NewItem = MakeShareable(new FRPGItemInfo);
		NewItem->SetInfo(Value, ItemType->Price, ItemType->Description, ItemType->Name, ItemType->InventoryType);
		_CharacterBagComponent->AddItem(NewItem);
	}
}

void ARPGGamePlayerState::LevelUp()
{
	_CharacterStat->Stat["STX"] += 5;
	_CharacterStat->Stat["MAXHP"] += 100;
	_CharacterStat->Stat["HP"] = _CharacterStat->Stat["MAXHP"];

	_CharacterStat->Stat["MAXMP"] += 50;
	_CharacterStat->Stat["MP"] = _CharacterStat->Stat["MAXMP"];
	_CharacterStat->Stat["LEVEL"]++;

	URPGCommonGameInstance* GI = Cast<URPGCommonGameInstance>(GetWorld()->GetGameInstance());
	URPGGameDataTableManager* DTManager = GI->GetDataTableManager();
	_CharacterStat->Stat["MAXEXP"] = DTManager->GetLevelToData(_CharacterStat->Stat["LEVEL"])->Exp;
	delegateLevelUp.ExecuteIfBound();
}

void ARPGGamePlayerState::UpdateQuestQuickInfo(FRPGQuestQuickInfo& Quest)
{
	_QuestQuickInfo = Quest;
	if(_QuestQuickInfo.TimeStamp != -1 ) _QuestQuickInfo.TimeStamp++;
}

void ARPGGamePlayerState::CheckQuestQuickInfo(EEnemyType EnemyTye)
{
	FString EnemyName;
	if (EnemyTye == EEnemyType::DOG) EnemyName = "Barghest";
	else EnemyName = "Griffon";
	for (auto& Item : _QuestQuickInfo.Current)
	{
		if (Item.Key != EnemyName) continue;
		Item.Value++;
		_QuestQuickInfo.TimeStamp++;
	}
}

TSharedPtr<FRPGItemInfo> ARPGGamePlayerState::GetFindItem(const FName& Name)
{
	return _CharacterBagComponent->FindItem(Name);
}


