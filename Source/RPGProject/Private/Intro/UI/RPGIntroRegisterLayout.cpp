// Fill out your copyright notice in the Description page of Project Settings.
#include "Intro/UI/RPGIntroRegisterLayout.h"
#include "Intro/UI/RPGIntroChangeSceneButton.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"

void URPGIntroRegisterLayout::NativeConstruct()
{
	Super::NativeConstruct();

	_RegisterButton = Cast<URPGIntroChangeSceneButton>(GetWidgetFromName(TEXT("RegisterButton")));
	_RegisterButton->SetWidgetState(EIntroUIWidgetState::Register);
	_RegisterButton->delegateUpdateSceneClick.AddDynamic(this, &URPGIntroRegisterLayout::OnClicked);

	_ExitButton = Cast<URPGIntroChangeSceneButton>(GetWidgetFromName(TEXT("ExitButton")));
	_ExitButton->SetWidgetState(EIntroUIWidgetState::Title);
	_ExitButton->delegateUpdateSceneClick.AddDynamic(this, &URPGIntroRegisterLayout::OnClicked);

	_UserNameEditBox = Cast<UEditableTextBox>(GetWidgetFromName("UserNameEditBox"));
	_PasswordEditBox = Cast<UEditableTextBox>(GetWidgetFromName("PasswordEditBox"));
	_CheckPasswordEditBox = Cast<UEditableTextBox>(GetWidgetFromName("CheckPasswordEditBox"));

	_RegisterInfo = Cast<UTextBlock>(GetWidgetFromName("RegisterInfoText"));
}

void URPGIntroRegisterLayout::OnClicked(EIntroUIWidgetState NewState)
{
	_RegisterInfo->SetText(FText::FromString("Test"));
	delegateChangeUI.ExecuteIfBound(NewState, 0);
}
