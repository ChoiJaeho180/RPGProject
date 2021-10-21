// Fill out your copyright notice in the Description page of Project Settings.
#include "Intro/UI/RPGIntroRegisterLayout.h"
#include "Intro/UI/RPGIntroChangeSceneButton.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Common/RPGCommonGameInstance.h"
#include "Components/CircularThrobber.h"

void URPGIntroRegisterLayout::NativeConstruct()
{
	Super::NativeConstruct();
	if (_bInit == false)
	{
		_RegisterButton = Cast<URPGIntroChangeSceneButton>(GetWidgetFromName(TEXT("RegisterButton")));
		_RegisterButton->SetWidgetState(EIntroDerivedWidgetState::MAIN_REGISTER);
		_RegisterButton->OnClicked.AddDynamic(this, &URPGIntroRegisterLayout::OnRegisterClicked);

		_ExitButton = Cast<URPGIntroChangeSceneButton>(GetWidgetFromName(TEXT("ExitButton")));
		_ExitButton->SetWidgetState(EIntroDerivedWidgetState::MAIN_LOGIN);
		_ExitButton->delegateUpdateSceneClick.AddDynamic(this, &URPGIntroRegisterLayout::OnChangeLayoutClicked);

		_UserNameEditBox = Cast<UEditableTextBox>(GetWidgetFromName("UserNameEditBox"));
		_PasswordEditBox = Cast<UEditableTextBox>(GetWidgetFromName("PasswordEditBox"));
		_CheckPasswordEditBox = Cast<UEditableTextBox>(GetWidgetFromName("CheckPasswordEditBox"));

		_LoadingCircle = Cast<UCircularThrobber>(GetWidgetFromName("LoadingCircle"));
		_LoadingCircle->SetVisibility(ESlateVisibility::Hidden);

		_RegisterInfo = Cast<UTextBlock>(GetWidgetFromName("RegisterInfoText"));
		_bInit = true;
	}
}

void URPGIntroRegisterLayout::OnChangeLayoutClicked(EIntroDerivedWidgetState NewState)
{
	//_RegisterInfo->SetText(FText::FromString("Test"));

	delegateSendLayoutChange.ExecuteIfBound(NewState, 0);
}

void URPGIntroRegisterLayout::OnRegisterClicked()
{
	FString Password = _PasswordEditBox->GetText().ToString();
	FString CheckPassword = _CheckPasswordEditBox->GetText().ToString();
	if (Password != CheckPassword)
	{
		_RegisterInfo->SetText(FText::FromString("Check the Password!"));
		return;
	}
	_LoadingCircle->SetVisibility(ESlateVisibility::Visible);
	URPGCommonGameInstance* GameInstance = Cast<URPGCommonGameInstance>(GetGameInstance());
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	JsonObject->SetStringField("ID", _UserNameEditBox->GetText().ToString());
	JsonObject->SetStringField("Password", Password);
	GameInstance->PostRequest("/users/register", JsonObject);

}

void URPGIntroRegisterLayout::SetRestResult(const FString& ResultCode)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{	
		_RegisterInfo->SetText(FText::FromString(ResultCode));
		_LoadingCircle->SetVisibility(ESlateVisibility::Hidden);

	});

}
