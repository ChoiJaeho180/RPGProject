// Fill out your copyright notice in the Description page of Project Settings.
#include "Intro/UI/RPGIntroInputCharacterInfoLayout.h"
#include "Intro/UI/RPGIntroChangeWidgetButton.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Common/RPGCommonGameInstance.h"

void URPGIntroInputCharacterInfoLayout::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (_bInit == false)
	{
		_RegisterButton = Cast<URPGIntroChangeWidgetButton>(GetWidgetFromName(TEXT("CharacterRegisterButton")));
		_RegisterButton->SetWidgetState(EIntroUIWidgetState::LOBBY);
		_RegisterButton->delegateUpdateWidgetClick.AddDynamic(this, &URPGIntroInputCharacterInfoLayout::OnRequest);

		_CancelButton = Cast<URPGIntroChangeWidgetButton>(GetWidgetFromName(TEXT("CancelButton")));
		_CancelButton->SetWidgetState(EIntroUIWidgetState::LOBBY);
		_CancelButton->delegateUpdateWidgetClick.AddDynamic(this, &URPGIntroInputCharacterInfoLayout::OnChangeWidgetClicked);

		_UserNameEditBox = Cast<UEditableTextBox>(GetWidgetFromName("UserNameEditBox"));
		_bInit = true;
	}
}

void URPGIntroInputCharacterInfoLayout::OnChangeWidget()
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		delegateSendWidgetChange.ExecuteIfBound(EIntroUIWidgetState::LOBBY, 0);
	});
}

void URPGIntroInputCharacterInfoLayout::OnChangeWidgetClicked(const EIntroUIWidgetState& NewState)
{
	delegateSendWidgetChange.ExecuteIfBound(NewState, 0);
}

void URPGIntroInputCharacterInfoLayout::OnRequest(const EIntroUIWidgetState& NewState)
{
	AsyncTask(ENamedThreads::AnyThread, [=]()
	{
		URPGCommonGameInstance* CurrentGI = Cast<URPGCommonGameInstance>(GetGameInstance());
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
		JsonObject->SetStringField("Name", _UserNameEditBox->Text.ToString());
		JsonObject->SetStringField("Job", "Warrior");
		CurrentGI->PostRequest(_LoginUri, JsonObject);
	});
}

