// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/RPGGamePlayerState.h"
#include "Game/RPGGameCharacterBagComponent.h"

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


