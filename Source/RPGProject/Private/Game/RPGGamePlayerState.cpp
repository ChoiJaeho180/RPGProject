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

void ARPGGamePlayerState::InitData(TArray<FRPGRestItem> RestItemData)
{
	_CharacterBagComponent->InitData(RestItemData);
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


