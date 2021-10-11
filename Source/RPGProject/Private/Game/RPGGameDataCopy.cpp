// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/RPGGameDataCopy.h"
#include "Game/RPGGamePlayerState.h"
#include "Game/RPGGameCharacterBagComponent.h"

// Sets default values
ARPGGameDataCopy::ARPGGameDataCopy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	_CharacterStat = MakeShareable(new FCharacterStat());
	_CharacterMoney = MakeShareable(new FMoney());
}

// Called when the game starts or when spawned
void ARPGGameDataCopy::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	_CheckStat = Controller->GetPlayerState<ARPGGamePlayerState>();
}

void ARPGGameDataCopy::CheckCharacterStat()
{
	TSharedPtr<FCharacterStat> CharacterStat = _CheckStat->GetCharacterStat();
	if (CharacterStat->TimeStamp == _CharacterStat->TimeStamp)
		return;
	_CharacterStat->SetInfo(CharacterStat);
}

void ARPGGameDataCopy::CheckCharacterItems()
{
	URPGGameCharacterBagComponent* BagComoponent = _CheckStat->GetCharacterBag();
	TArray<TSharedPtr<FRPGItemInfo>> CharacterItems = BagComoponent->GetChartacterItems();
	if (_CharacterItemInfo.Num() != CharacterItems.Num())
	{
		_CharacterItemInfo = CharacterItems;
		_bInitFirstItem = true;
		return;
	}
	for (int i = 0; i < CharacterItems.Num(); i++)
	{
		if (CharacterItems[i]->TimeStamp == _CharacterItemInfo[i]->TimeStamp)
			continue;
		_CharacterItemInfo[i] = CharacterItems[i];
		_bInitFirstItem = true;
	}
}

void ARPGGameDataCopy::CehckkCharacterMoney()
{
	auto Money = _CheckStat->GetCharacterBag()->GetCharacterMoney();
	if (_CharacterMoney->TimeStamp == Money->TimeStamp)
		return;
	_CharacterMoney = Money;
}

// Called every frame
void ARPGGameDataCopy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	_DeltaTime += DeltaTime;
	if (_DeltaTime < STARNDARD_TIME)
		return;

	CheckCharacterStat();
	CheckCharacterItems();
	CehckkCharacterMoney();

	_DeltaTime = 0.f;
}

