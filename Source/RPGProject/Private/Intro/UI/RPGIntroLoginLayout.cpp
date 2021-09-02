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
	_RegisterButton->delegateUpdateSceneClick.AddDynamic(this, &URPGIntroLoginLayout::OnChangeLayoutClicked);

	_ExitButton = Cast<URPGIntroChangeSceneButton>(GetWidgetFromName(TEXT("ExitButton")));
	_ExitButton->SetWidgetState(EIntroDerivedWidgetState::MAIN_TITLE);
	_ExitButton->delegateUpdateSceneClick.AddDynamic(this, &URPGIntroLoginLayout::OnChangeLayoutClicked);

	_LoginButton = Cast<URPGIntroChangeSceneButton>(GetWidgetFromName(TEXT("LoginButton")));
	_LoginButton->SetWidgetState(EIntroDerivedWidgetState::TO_LOBBY);
	_LoginButton->delegateUpdateSceneClick.AddDynamic(this, &URPGIntroLoginLayout::OnChangeWidgetClicked);

	
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
		_FadeInAnimation = WidgetClass->Animations[i];
		delegateEndedFadeIn.BindDynamic(this, &URPGIntroLoginLayout::OnFadeInAnimEnded);
		BindToAnimationFinished(_FadeInAnimation, delegateEndedFadeIn);
		break;
	}
}

void URPGIntroLoginLayout::OnChangeWidgetClicked(EIntroDerivedWidgetState NewState)
{
	//OnMontageEnded : animation finish ¸Þ¼­µå
	AsyncTask(ENamedThreads::AnyThread, [=]()
	{
		//call RestApi func
		//~~~
		FPlatformProcess::Sleep(1);
		AsyncTask(ENamedThreads::GameThread, [=]()
		{
			_FadeInImage->SetVisibility(ESlateVisibility::Visible);
			PlayAnimation(_FadeInAnimation);
		});
	});
}

void URPGIntroLoginLayout::OnFadeInAnimEnded()
{
	delegateChangeUI.ExecuteIfBound(EIntroDerivedWidgetState::TO_LOBBY, 0);
	_FadeInImage->SetVisibility(ESlateVisibility::Hidden);
}

void URPGIntroLoginLayout::OnChangeLayoutClicked(EIntroDerivedWidgetState NewState)
{
	delegateChangeUI.ExecuteIfBound(NewState, 0);
}
