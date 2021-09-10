// Fill out your copyright notice in the Description page of Project Settings.

#include "Intro/UI/RPGIntroCreateCharacterLayout.h"
#include "Intro/UI/RPGIntroChooseJobButton.h"
#include "Intro/UI/RPGIntroInputCharacterInfoLayout.h"

void URPGIntroCreateCharacterLayout::NativeConstruct()
{
	Super::NativeConstruct();
	if (_bInit == false)
	{
		_JobButton = Cast<URPGIntroChooseJobButton>(GetWidgetFromName("RPGIntroChooseJobButton"));
		_JobButton->delegateActiveInputCharacterInfo.BindUObject(this, &URPGIntroCreateCharacterLayout::ActiveInputCharacterLayout);
		
		_InputCharacterLayout = Cast<URPGIntroInputCharacterInfoLayout>(GetWidgetFromName("WB_CreateCharacter_Inpu_Layout"));
		_InputCharacterLayout->delegateSendWidgetChange.BindUObject(this, &URPGIntroCreateCharacterLayout::OnChangeWidget);
		_bInit = true;
	}
}

void URPGIntroCreateCharacterLayout::ActiveInputCharacterLayout()
{
	ESlateVisibility NewState = _InputCharacterLayout->GetVisibility() == ESlateVisibility::Visible ? ESlateVisibility::Hidden : ESlateVisibility::Visible;
	_InputCharacterLayout->SetVisibility(NewState);
}

void URPGIntroCreateCharacterLayout::OnChangeWidget(const EIntroUIWidgetState& NewState, const int& ZOrder)
{
	delegateSendWidgetChange.ExecuteIfBound(NewState, ZOrder);
}
