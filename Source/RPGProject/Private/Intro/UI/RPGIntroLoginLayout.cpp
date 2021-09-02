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
}


void URPGIntroLoginLayout::OnChangeWidgetClicked(EIntroDerivedWidgetState NewState)
{
	AsyncTask(ENamedThreads::AnyThread, [=]()
	{
		//call RestApi func
		//~~~
		FPlatformProcess::Sleep(1);
		AsyncTask(ENamedThreads::GameThread, [=]()
		{
			delegateSendWidgetChange.ExecuteIfBound(NewState, 0);
		});
	});
}

void URPGIntroLoginLayout::OnChangeLayoutClicked(EIntroDerivedWidgetState NewState)
{
	delegateSendLayoutChange.ExecuteIfBound(NewState, 0);
}
