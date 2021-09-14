// Fill out your copyright notice in the Description page of Project Settings.
#include "Intro/UI/RPGIntroLobbySlotInfoLayout.h"
#include "Intro/UI/RPGIntroLobbyInfoLayout.h"
#include "Intro/UI/RPGIntroChooseCharacterButton.h"
#include "Intro/RPGIntroController.h"

void URPGIntroLobbySlotInfoLayout::NativeConstruct()
{
	Super::NativeConstruct();
	if (_bInit == false)
	{
		_ChooseButton = Cast<URPGIntroChooseCharacterButton>(GetWidgetFromName("CharacterButton"));
		_ChooseButton->OnClicked.AddDynamic(this, &URPGIntroLobbySlotInfoLayout::OnClick);
		_BackgroundImage = Cast<UImage>(GetWidgetFromName("BackgroundImage"));
		_LevelText = Cast<UTextBlock>(GetWidgetFromName("LevelText"));
		_JobText = Cast<UTextBlock>(GetWidgetFromName("JobText"));
		_NameText = Cast<UTextBlock>(GetWidgetFromName("NameText"));

		_bInit = true;
	}
}

void URPGIntroLobbySlotInfoLayout::OnClick()
{
	FString Name = _NameText->GetText().ToString();
	delegateChooseNewSlot.ExecuteIfBound(_ScarecrowIndex, Name);
}

void URPGIntroLobbySlotInfoLayout::SetBackgroundColor(bool bChoose)
{
	if (bChoose == true)
	{
		_BackgroundImage->SetColorAndOpacity(FLinearColor(0.5f, 0.045f, 0.04f));
	}
	else
	{
		_BackgroundImage->SetColorAndOpacity(FLinearColor(0.04f, 0.045f, 0.08f));
	}
}
