// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/Enemy/RPGGameEnemyHPWidget.h"
#include "Game/Enemy/RPGGameEnemyStatComponent.h"
#include "Components/ProgressBar.h"

void URPGGameEnemyHPWidget::NativeConstruct()
{
	Super::NativeConstruct();
	_HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("Bar")));
	UpdateHPWidget();
}

void URPGGameEnemyHPWidget::BindCharacterStat(URPGGameEnemyStatComponent* NewStat)
{
	_CurrentCharacterStat = NewStat;
	_CurrentCharacterStat->OnHPChanged.AddUObject(this, &URPGGameEnemyHPWidget::UpdateHPWidget);
}

void URPGGameEnemyHPWidget::UpdateHPWidget()
{
	if (_CurrentCharacterStat.IsValid())
	{
		if (nullptr != _HPProgressBar)
		{
			_HPProgressBar->SetPercent(_CurrentCharacterStat->GetHPRatio());
		}
	}
}
