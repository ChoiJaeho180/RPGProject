// Fill out your copyright notice in the Description page of Project Settings.
#include "Intro/UI/RPGIntroLoginLayout.h"
#include "Intro/UI/RPGIntroChangeSceneButton.h"
#include "Intro/UI/RPGIntroChangeWidgetButton.h"
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

	if (_bInit == false)
	{
		_RegisterButton = Cast<URPGIntroChangeSceneButton>(GetWidgetFromName(TEXT("RegisterButton")));
		_RegisterButton->SetWidgetState(EIntroDerivedWidgetState::MAIN_REGISTER);
		_RegisterButton->delegateUpdateSceneClick.AddDynamic(this, &URPGIntroLoginLayout::OnChangeLayoutClicked);

		_ExitButton = Cast<URPGIntroChangeSceneButton>(GetWidgetFromName(TEXT("ExitButton")));
		_ExitButton->SetWidgetState(EIntroDerivedWidgetState::MAIN_TITLE);
		_ExitButton->delegateUpdateSceneClick.AddDynamic(this, &URPGIntroLoginLayout::OnChangeLayoutClicked);

		_LoginButton = Cast<URPGIntroChangeWidgetButton>(GetWidgetFromName(TEXT("LoginButton")));
		_LoginButton->SetWidgetState(EIntroUIWidgetState::LOBBY);
		_LoginButton->delegateUpdateWidgetClick.AddDynamic(this, &URPGIntroLoginLayout::OnChangeWidgetClicked);

		_UserNameEditBox = Cast<UEditableTextBox>(GetWidgetFromName("UserNameEditBox"));
		_PasswordEditBox = Cast<UEditableTextBox>(GetWidgetFromName("PasswordEditBox"));

		_LoginInfoText = Cast<UTextBlock>(GetWidgetFromName("LoginInfoText"));
		_LoadingCircle = Cast<UCircularThrobber>(GetWidgetFromName("LoadingCircle"));
		_bInit = true;
	}
}


void URPGIntroLoginLayout::OnChangeWidgetClicked(const EIntroUIWidgetState& NewState)
{
	if (_UserNameEditBox->Text.IsEmpty() || _PasswordEditBox->Text.IsEmpty())
	{
		_LoginInfoText->SetText(FText::FromString("ID or Password is Empty"));;
		return;
	}

	_LoadingCircle->SetVisibility(ESlateVisibility::Visible);
	_TempChangeWidgetState = NewState;

	AsyncTask(ENamedThreads::AnyThread, [=]()
	{
		URPGCommonGameInstance* CurrentGI = Cast<URPGCommonGameInstance>(GetGameInstance());
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
		JsonObject->SetStringField("ID", _UserNameEditBox->Text.ToString());
		JsonObject->SetStringField("Password", _PasswordEditBox->Text.ToString());
		CurrentGI->PostRequest(_LoginUri, JsonObject);
	});
}

void URPGIntroLoginLayout::OnChangeWidget()
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		delegateSendWidgetChange.ExecuteIfBound(_TempChangeWidgetState, 0);
		OnChangeInitProperty();
		_TempChangeWidgetState = EIntroUIWidgetState::NONE;
	});
}

void URPGIntroLoginLayout::RegistFailedEvent()
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		_LoginInfoText->SetText(FText::FromString("ID or Password is incorrect"));
		GetWorld()->GetTimerManager().SetTimer(
			_TimerHandle,
			this,
			&URPGIntroLoginLayout::ReceiveEvent,
			3,
			false
		);
	});
}

void URPGIntroLoginLayout::ReceiveEvent()
{
	OnChangeInitProperty();
}

void URPGIntroLoginLayout::OnChangeInitProperty()
{
	_LoadingCircle->SetVisibility(ESlateVisibility::Hidden);
	_TempChangeWidgetState = EIntroUIWidgetState::NONE;
	_LoginInfoText->SetText(FText::GetEmpty());
}

void URPGIntroLoginLayout::OnChangeLayoutClicked(EIntroDerivedWidgetState NewState)
{
	OnChangeInitProperty();
	delegateSendLayoutChange.ExecuteIfBound(NewState, 0);
}
