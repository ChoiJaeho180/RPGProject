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
	_RegisterButton->SetWidgetState(EIntroDerivedWidgetState::MAIN_REGISTER);
	_RegisterButton->delegateUpdateSceneClick.AddDynamic(this, &URPGIntroRegisterLayout::OnChangeLayoutClicked);

	_ExitButton = Cast<URPGIntroChangeSceneButton>(GetWidgetFromName(TEXT("ExitButton")));
	_ExitButton->SetWidgetState(EIntroDerivedWidgetState::MAIN_LOGIN);
	_ExitButton->delegateUpdateSceneClick.AddDynamic(this, &URPGIntroRegisterLayout::OnChangeLayoutClicked);

	_UserNameEditBox = Cast<UEditableTextBox>(GetWidgetFromName("UserNameEditBox"));
	_PasswordEditBox = Cast<UEditableTextBox>(GetWidgetFromName("PasswordEditBox"));
	_CheckPasswordEditBox = Cast<UEditableTextBox>(GetWidgetFromName("CheckPasswordEditBox"));

	_RegisterInfo = Cast<UTextBlock>(GetWidgetFromName("RegisterInfoText"));
}

void URPGIntroRegisterLayout::OnChangeLayoutClicked(EIntroDerivedWidgetState NewState)
{
	_RegisterInfo->SetText(FText::FromString("Test"));
	delegateSendLayoutChange.ExecuteIfBound(NewState, 0);
}
