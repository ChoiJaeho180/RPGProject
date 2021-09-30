// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameUserInfoLayout.h"
#include "Game/UI/RPGGameProgressBarLayout.h"
#include "Game/UI/RPGGameActionBarLayout.h"
#include "Components/ProgressBar.h"
#include "Common/RPGCommonGameInstance.h"
#include "Game/UI/RPGGameSpecialBar.h"

void URPGGameUserInfoLayout::NativeConstruct()
{
	Super::NativeConstruct();
	if (_CharacterStat == nullptr)
	{
		_CharacterStat = MakeShareable(new FCharacterStat);
	}
	_SpecialBar = Cast<URPGGameSpecialBar>(GetWidgetFromName("SpecialBar"));
	_HPBar = Cast<URPGGameProgressBarLayout>(GetWidgetFromName("HPBar"));
	_MPBar = Cast<URPGGameProgressBarLayout>(GetWidgetFromName("MPBar"));
	_ActionBar = Cast<URPGGameActionBarLayout>(GetWidgetFromName("ActionBar"));
	_ExpBar = Cast<URPGGameProgressBarLayout>(GetWidgetFromName("ExpBar"));
	InteractionDeltaTime = 0;
	SetGameDataCopy();
}

void URPGGameUserInfoLayout::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	InteractionDeltaTime += InDeltaTime;
	if (InteractionDeltaTime < STARNDARD_TIME)
		return;

	InteractionDeltaTime = 0.f;
	TSharedPtr<FCharacterStat> CheckStat = GameDataCopy->GetCharacterStat();
	if (CheckStat->TimeStamp == _CharacterStat->TimeStamp)
		return;

	_CharacterStat->SetInfo(CheckStat);
	UpdateProperty();
}

void URPGGameUserInfoLayout::SetGameDataCopy()
{
	if (GameDataCopy != nullptr)
		return;

	GameDataCopy = Cast<URPGCommonGameInstance>(GetGameInstance())->GetDataCopyClass();
}

void URPGGameUserInfoLayout::UpdateProperty()
{
	float NewSpecialPercent = (float)_CharacterStat->SpecialState * 0.01f;
	_SpecialBar->SetSpecialBarPercent(NewSpecialPercent);

	float NewHPPercent = (float)_CharacterStat->CurrentHP / _CharacterStat->MaxHP;
	_HPBar->UpdateProgressBar(NewHPPercent);

	float NewMPPercent = (float)_CharacterStat->CurrentMP / _CharacterStat->MaxMP;
	_MPBar->UpdateProgressBar(NewMPPercent);
}
