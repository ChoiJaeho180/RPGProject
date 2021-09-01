// Fill out your copyright notice in the Description page of Project Settings.
#include "../../../Public/Intro/UI/RPGIntroTitleLayout.h"
#include "Animation/WidgetAnimation.h"
#include "Components/Button.h"

void URPGIntroTitleLayout::NativeConstruct()
{
	Super::NativeConstruct();

	_StartGameButton = Cast<UButton>(GetWidgetFromName(TEXT("StartGameButton")));
	_StartGameButton->OnClicked.AddDynamic(this, &URPGIntroTitleLayout::OnStartClicked);

	PlayAnimations();
}

void URPGIntroTitleLayout::PlayAnimations()
{
	UWidgetBlueprintGeneratedClass* WidgetClass = GetWidgetTreeOwningClass();
	for (int i = 0; i < WidgetClass->Animations.Num(); i++)
	{
		if (WidgetClass->Animations[i]->GetName() != TEXT("TitleAnimation_INST"))
			continue;

		PlayAnimation(WidgetClass->Animations[i]);
		break;
	}
}

void URPGIntroTitleLayout::OnStartClicked()
{
	delegateChangeUI.ExecuteIfBound(EIntroDerivedWidgetState::MAIN_LOGIN, 0);
}
