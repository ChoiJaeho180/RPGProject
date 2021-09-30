// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameSpecialBar.h"
#include "Components/Image.h"

void URPGGameSpecialBar::NativeConstruct()
{
	Super::NativeConstruct();
	_SpecialBar = Cast<UImage>(GetWidgetFromName(TEXT("SpecialImage")));
	_MatInst = _SpecialBar->GetDynamicMaterial();
	_PercentRatio = 0.f;
}

void URPGGameSpecialBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (_NewPercent == _CurrentPercent)
		return;

	float result = FMath::Lerp(_CurrentPercent, _NewPercent, _PercentRatio);

	_MatInst->SetScalarParameterValue(FName("percentage"), result);

	_PercentRatio += PLUS_PERCENT_VALUE;
	if (_PercentRatio >= STOP_LERP_VALUE)
	{
		_PercentRatio = 0;
	}
}

void URPGGameSpecialBar::SetSpecialBarPercent(float NewPercent)
{
	_MatInst->GetScalarParameterValue(FName("percentage"), _CurrentPercent);
	_PercentRatio = 0;
	_NewPercent = NewPercent;
}
