// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameProgressBarLayout.h"
#include "Game/UI/RPGGameProgressBar.h"
#include "Components/TextBlock.h"

void URPGGameProgressBarLayout::NativeConstruct()
{
	Super::NativeConstruct();
	_ProgressBar = Cast<URPGGameProgressBar>(GetWidgetFromName("Bar"));
	_CurrentStatText = Cast<UTextBlock>(GetWidgetFromName("CurrentStatText"));
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

void URPGGameProgressBarLayout::UpdateProgressBar(float Percent, int CurrentStat, int MaxStat, bool bExp)
{
	_NewPercent = Percent;
	_PercentRatio = INIT_PERCENT_VALUE;
	if (_CurrentStatText == nullptr) return;
	FString NewText = FString::FromInt(CurrentStat) + " / " + FString::FromInt(MaxStat);
	if (bExp == true)
	{
		
		NewText = NewText + "  " + FString::SanitizeFloat(round(Percent * 10000) / 100) + "%";
	}
	_CurrentStatText->SetText(FText::FromString(NewText));
}
