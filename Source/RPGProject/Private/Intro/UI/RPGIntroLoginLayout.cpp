// Fill out your copyright notice in the Description page of Project Settings.
#include "Intro/UI/RPGIntroLoginLayout.h"
#include "Intro/UI/RPGIntroChangeSceneButton.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"

void URPGIntroLoginLayout::NativeConstruct()
{
	Super::NativeConstruct();

	_RegisterButton = Cast<URPGIntroChangeSceneButton>(GetWidgetFromName(TEXT("RegisterButton")));
	_RegisterButton->SetWidgetState(EIntroUIWidgetState::Register);
	_RegisterButton->delegateUpdateSceneClick.AddDynamic(this, &URPGIntroLoginLayout::OnClicked);

	_ExitButton = Cast<URPGIntroChangeSceneButton>(GetWidgetFromName(TEXT("ExitButton")));
	_ExitButton->SetWidgetState(EIntroUIWidgetState::Title);
	_ExitButton->delegateUpdateSceneClick.AddDynamic(this, &URPGIntroLoginLayout::OnClicked);

	_LoginButton = Cast<URPGIntroChangeSceneButton>(GetWidgetFromName(TEXT("LoginButton")));
	_LoginButton->SetWidgetState(EIntroUIWidgetState::Login);
	_LoginButton->delegateUpdateSceneClick.AddDynamic(this, &URPGIntroLoginLayout::OnClicked);

	_UserNameEditBox = Cast<UEditableTextBox>(GetWidgetFromName("UserNameEditBox"));
	_PasswordEditBox = Cast<UEditableTextBox>(GetWidgetFromName("PasswordEditBox"));
}

void URPGIntroLoginLayout::OnClicked(EIntroUIWidgetState NewState)
{
	delegateChangeUI.ExecuteIfBound(NewState, 0);
}
