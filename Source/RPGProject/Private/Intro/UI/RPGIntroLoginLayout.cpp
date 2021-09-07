// Fill out your copyright notice in the Description page of Project Settings.
#include "Intro/UI/RPGIntroLoginLayout.h"
#include "Intro/UI/RPGIntroChangeSceneButton.h"
#include "Common/RPGCommonGameInstance.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/CircularThrobber.h"
#include "Animation/WidgetAnimation.h"
#include "Dom/JsonObject.h"
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

	_LoginInfoText = Cast<UTextBlock>(GetWidgetFromName("LoginInfoText"));
	_LoadingCircle = Cast<UCircularThrobber>(GetWidgetFromName("LoadingCircle"));
}


void URPGIntroLoginLayout::OnChangeWidgetClicked(EIntroDerivedWidgetState NewState)
{
	if (_UserNameEditBox->Text.IsEmpty() || _PasswordEditBox->Text.IsEmpty())
	{
		_LoginInfoText->SetText(FText::FromString("ID or Password is Empty"));;
		return;
	}
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	JsonObject->SetStringField("ID", _UserNameEditBox->Text.ToString());
	JsonObject->SetStringField("Password", _PasswordEditBox->Text.ToString());

	_LoadingCircle->SetVisibility(ESlateVisibility::Visible);
	_TempChangeWidget = NewState;

	AsyncTask(ENamedThreads::AnyThread, [=]()
	{
		URPGCommonGameInstance* CurrentGI = Cast<URPGCommonGameInstance>(GetGameInstance());
		CurrentGI->PostRequest(_LoginUri, JsonObject);
	});
}

void URPGIntroLoginLayout::OnChangeWidget()
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		OnChangeInit();
		_TempChangeWidget = EIntroDerivedWidgetState::NONE;
	});
}

void URPGIntroLoginLayout::OnChangeInit()
{
	_LoadingCircle->SetVisibility(ESlateVisibility::Hidden);
	_TempChangeWidget = EIntroDerivedWidgetState::NONE;
	_LoginInfoText->SetText(FText::GetEmpty());
}

void URPGIntroLoginLayout::OnChangeLayoutClicked(EIntroDerivedWidgetState NewState)
{
	OnChangeInit();
	delegateSendLayoutChange.ExecuteIfBound(NewState, 0);
}
