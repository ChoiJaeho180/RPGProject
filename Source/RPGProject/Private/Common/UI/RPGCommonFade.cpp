// Fill out your copyright notice in the Description page of Project Settings.
#include "Common/UI/RPGCommonFade.h"
#include "Components/Image.h"

void URPGCommonFade::NativePreConstruct()
{
	Super::NativePreConstruct();
	SetFadeAnimation();
}

void URPGCommonFade::NativeConstruct()
{
	Super::NativeConstruct();

	_FadeState = ECommonFadeState::NONE;

	_FadeImage = Cast<UImage>(GetWidgetFromName(TEXT("FadeImage")));

}

void URPGCommonFade::SetFadeAnimation()
{
	_FadeAnimations.Add(GetAnimation("FadeIn_INST"));
	_FadeAnimations.Add(GetAnimation("FadeOut_INST"));
	delegateEndedEffect.BindDynamic(this, &URPGCommonFade::OnEndedFadeInAnim);
	BindToAnimationFinished(_FadeAnimations[0], delegateEndedEffect);
	BindToAnimationFinished(_FadeAnimations[1], delegateEndedEffect);
}

void URPGCommonFade::OnEndedFadeInAnim()
{
	if (_FadeState == ECommonFadeState::FADE_IN)
	{
		if (_bChangeLevel == true)
		{
			delegateChangeLevel.ExecuteIfBound();
			return;
		}
		_FadeState = ECommonFadeState::FADE_OUT;
		delegateAttachWidget.ExecuteIfBound();
		PlayAnim();
	}
	else
	{
		_FadeState = ECommonFadeState::NONE;
		delegateChangeMap.ExecuteIfBound();
		//delegateAttachWidget.ExecuteIfBound();
		_FadeImage->SetVisibility(ESlateVisibility::Hidden);
	}
}

void URPGCommonFade::SetFadeState(ECommonFadeState NewState)
{
	_FadeState = NewState;
	if (_FadeState == ECommonFadeState::FADE_OUT)
	{
		_FadeImage->SetOpacity(1.f);
		_FadeImage->SetVisibility(ESlateVisibility::Visible);
	}
}

void URPGCommonFade::PlayAnim()
{
	if (_FadeState == ECommonFadeState::NONE)
		_FadeState = ECommonFadeState::FADE_IN;
	
	if (_FadeAnimations.Num() == 0 || _FadeImage == nullptr)
		return;

	_FadeImage->SetVisibility(ESlateVisibility::Visible);
	int FadeIndex = (int)_FadeState;

	if (_FadeAnimations[FadeIndex] == nullptr)
		return;

	PlayAnimation(_FadeAnimations[FadeIndex]);
}
