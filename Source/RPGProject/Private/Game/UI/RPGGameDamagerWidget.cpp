// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameDamagerWidget.h"
#include "Components/TextBlock.h"

void URPGGameDamagerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	_DamageText = Cast<UTextBlock>(GetWidgetFromName("DamageText"));
	SetFadeAnimation();
	delegateEndedEffect.BindDynamic(this, &URPGGameDamagerWidget::OnEndedFadeInAnim);
	BindToAnimationFinished(_FadeAnimation, delegateEndedEffect);

	
}

void URPGGameDamagerWidget::SetFadeAnimation()
{
	UWidgetBlueprintGeneratedClass* WidgetClass = GetWidgetTreeOwningClass();
	for (int i = 0; i < WidgetClass->Animations.Num(); i++)
	{
		if (WidgetClass->Animations[i]->GetName() != "Fade_INST")
			continue;
		_FadeAnimation = WidgetClass->Animations[i];
		break;
	}
}

void URPGGameDamagerWidget::SetDamageText(FString NewText)
{
	_DamageText->SetText(FText::FromString(NewText));
}

void URPGGameDamagerWidget::PlayFadeAnimation()
{
	PlayAnimation(_FadeAnimation);
}

void URPGGameDamagerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (_Alpha > 1.0f) return;
	FVector2D NewPosition = FMath::Lerp(_InitPosition, _GoalPosition, _Alpha);
	SetPositionInViewport(NewPosition);
	_Alpha += 0.01f;
}

void URPGGameDamagerWidget::OnEndedFadeInAnim()
{
	RemoveFromViewport();
	UE_LOG(LogTemp, Warning, TEXT("Remove"));
}
