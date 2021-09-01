// Fill out your copyright notice in the Description page of Project Settings.
#include "Intro/UI/RPGIntroLoginLayout.h"
#include "Intro/UI/RPGIntroChangeSceneButton.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Animation/WidgetAnimation.h"
#include "Components/Image.h"
#include "Async/Async.h"

void URPGIntroLoginLayout::NativeConstruct()
{
	Super::NativeConstruct();

	_RegisterButton = Cast<URPGIntroChangeSceneButton>(GetWidgetFromName(TEXT("RegisterButton")));
	_RegisterButton->SetWidgetState(EIntroDerivedWidgetState::MAIN_REGISTER);
	_RegisterButton->delegateUpdateSceneClick.AddDynamic(this, &URPGIntroLoginLayout::OnClicked);

	_ExitButton = Cast<URPGIntroChangeSceneButton>(GetWidgetFromName(TEXT("ExitButton")));
	_ExitButton->SetWidgetState(EIntroDerivedWidgetState::MAIN_TITLE);
	_ExitButton->delegateUpdateSceneClick.AddDynamic(this, &URPGIntroLoginLayout::OnClicked);

	_LoginButton = Cast<URPGIntroChangeSceneButton>(GetWidgetFromName(TEXT("LoginButton")));
	_LoginButton->SetWidgetState(EIntroDerivedWidgetState::TO_LOBBY);
	_LoginButton->delegateUpdateSceneClick.AddDynamic(this, &URPGIntroLoginLayout::OnClicked);

	
	_UserNameEditBox = Cast<UEditableTextBox>(GetWidgetFromName("UserNameEditBox"));
	_PasswordEditBox = Cast<UEditableTextBox>(GetWidgetFromName("PasswordEditBox"));

	_FadeInImage = Cast<UImage>(GetWidgetFromName(TEXT("FadeInImage")));
	SetFadeInAnimation();
}

void URPGIntroLoginLayout::SetFadeInAnimation()
{
	UWidgetBlueprintGeneratedClass* WidgetClass = GetWidgetTreeOwningClass();
	for (int i = 0; i < WidgetClass->Animations.Num(); i++)
	{
		if (WidgetClass->Animations[i]->GetName() != TEXT("FadeInAni_INST"))
			continue;
		_FadeInImage->Visibility = ESlateVisibility::Visible;
		PlayAnimation(WidgetClass->Animations[i]);
		_FadeInAnimation = WidgetClass->Animations[i];
		break;
	}
}

void URPGIntroLoginLayout::OnClicked(EIntroDerivedWidgetState NewState)
{
	AsyncTask(ENamedThreads::AnyThread, [=]()
	{
		AsyncTask(ENamedThreads::GameThread, [=]()
		{
			_FadeInImage->SetVisibility(ESlateVisibility::Visible);
			PlayAnimation(_FadeInAnimation);
		});
		 FPlatformProcess::Sleep(3);
	});
	if (NewState == EIntroDerivedWidgetState::TO_LOBBY)
	{
		//OnMontageEnded : animation finish ¸Þ¼­µå
	
	}
	delegateChangeUI.ExecuteIfBound(NewState, 0);
}
