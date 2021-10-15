// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameProgressBarLayout.h"
#include "Game/UI/RPGGameProgressBar.h"



void URPGGameProgressBarLayout::NativeConstruct()
{
	Super::NativeConstruct();
	_ProgressBar = Cast<URPGGameProgressBar>(GetWidgetFromName("Bar"));
	
}

void URPGGameProgressBarLayout::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick( MyGeometry, InDeltaTime);

	if (_NewPercent < INIT_PERCENT_VALUE)
		return;

	float result = FMath::Lerp(_ProgressBar->Percent, _NewPercent, _PercentRatio);

	_ProgressBar->SetPercent(result);
	_PercentRatio += PLUS_PERCENT_VALUE;
}

void URPGGameProgressBarLayout::UpdateProgressBar(float Percent)
{
	_NewPercent = Percent;
	_PercentRatio = INIT_PERCENT_VALUE;
}
