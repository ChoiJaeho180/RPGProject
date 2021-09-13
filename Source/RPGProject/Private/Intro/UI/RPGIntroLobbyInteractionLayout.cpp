// Fill out your copyright notice in the Description page of Project Settings.


#include "Intro/UI/RPGIntroLobbyInteractionLayout.h"
#include "Intro/UI/RPGIntroChangeSceneButton.h"
#include "Intro/UI/RPGIntroChangeWidgetButton.h"

void URPGIntroLobbyInteractionLayout::NativeConstruct()
{
	Super::NativeConstruct();
	if (_bInit == false)
	{
		_BackButton = Cast<URPGIntroChangeWidgetButton>(GetWidgetFromName(TEXT("BackButton")));
		_BackButton->SetWidgetState(EIntroUIWidgetState::MAIN);
		_BackButton->delegateUpdateWidgetClick.AddDynamic(this, &URPGIntroLobbyInteractionLayout::OnChangeWidgetClicked);

		_StartButton = Cast<URPGIntroChangeWidgetButton>(GetWidgetFromName(TEXT("GameStartButton")));
		_StartButton->SetWidgetState(EIntroUIWidgetState::NEXT_LEVEL);
		_StartButton->delegateUpdateWidgetClick.AddDynamic(this, &URPGIntroLobbyInteractionLayout::OnChangeWidgetClicked);

		_NewCharacterButton = Cast<URPGIntroChangeWidgetButton>(GetWidgetFromName(TEXT("CreateButton")));
		_NewCharacterButton->SetWidgetState(EIntroUIWidgetState::CREATE);
		_NewCharacterButton->delegateUpdateWidgetClick.AddDynamic(this, &URPGIntroLobbyInteractionLayout::OnChangeWidgetClicked);
		_bInit = true;
	}
}

void URPGIntroLobbyInteractionLayout::OnChangeWidgetClicked(const EIntroUIWidgetState& NewState)
{
	UE_LOG(LogTemp, Warning, TEXT("aaaaa"));
	delegateSendWidgetChange.ExecuteIfBound(NewState, 0);
}