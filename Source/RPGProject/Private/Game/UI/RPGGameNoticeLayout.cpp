// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameNoticeLayout.h"
#include "Blueprint/WidgetTree.h"
#include "Components/ScaleBox.h"
#include "Animation/WidgetAnimation.h"
#include "Components/TextBlock.h"

void URPGGameNoticeLayout::PlayNoticeAnimation()
{
	_NoticeScaleBox->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	PlayAnimation(_NoticeAnimation, 0.0f);
}
void URPGGameNoticeLayout::NativeConstruct()
{
	Super::NativeConstruct();
	_NoticeScaleBox = Cast<UScaleBox>(GetWidgetFromName("NoticeScaleBox"));
	_NoticeText = Cast<UTextBlock>(GetWidgetFromName("NoticeText"));
	_NoticeScaleBox->SetVisibility(ESlateVisibility::Hidden);
	_NoticeAnimation = GetAnimation("test_INST");
}
UWidgetAnimation* URPGGameNoticeLayout::GetAnimation(const FString& AnimName)
{
	UWidgetAnimation* SearchAnim = nullptr;
	UWidgetBlueprintGeneratedClass* WidgetClass = GetWidgetTreeOwningClass();
	for (int i = 0; i < WidgetClass->Animations.Num(); i++)
	{
		if (WidgetClass->Animations[i]->GetName() != AnimName)
			continue;
		SearchAnim = WidgetClass->Animations[i];
		break;
	}
	return SearchAnim;
}

void URPGGameNoticeLayout::SetNoticeText(FText Text)
{
	_NoticeText->SetText(Text);
}
