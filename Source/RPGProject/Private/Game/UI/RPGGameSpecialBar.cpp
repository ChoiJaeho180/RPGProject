// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameSpecialBar.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void URPGGameSpecialBar::NativeConstruct()
{
	Super::NativeConstruct();
	_SpecialBar = Cast<UImage>(GetWidgetFromName(TEXT("SpecialImage")));
	_CurrentStatText = Cast<UTextBlock>(GetWidgetFromName("CurrentStatText"));
	_MatInst = _SpecialBar->GetDynamicMaterial();
	_PercentRatio = 0.f;
}

void URPGGameSpecialBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (_PercentRatio >= STOP_LERP_VALUE)
		return;

	float result = FMath::Lerp(_CurrentPercent, _NewPercent, _PercentRatio);

	_MatInst->SetScalarParameterValue(FName("percentage"), result);

	_PercentRatio += PLUS_PERCENT_VALUE;
}

void URPGGameSpecialBar::SetSpecialBarPercent(float NewPercent, int CurrentSpecialBar)
{
	_MatInst->GetScalarParameterValue(FName("percentage"), _CurrentPercent);
	_PercentRatio = 0;
	_NewPercent = NewPercent;
	if (_CurrentStatText == nullptr) return;
	_CurrentStatText->SetText(FText::FromString(FString::FromInt(CurrentSpecialBar) + " / " + FString::FromInt(100)));
}
