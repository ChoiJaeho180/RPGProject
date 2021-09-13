// Fill out your copyright notice in the Description page of Project Settings.
#include "Intro/UI/RPGIntroLobbySlotInfoLayout.h"
#include "Intro/UI/RPGIntroLobbyInfoLayout.h"
#include "Intro/UI/RPGIntroChooseCharacterButton.h"
#include "Intro/RPGIntroController.h"

void URPGIntroLobbySlotInfoLayout::NativeConstruct()
{
	Super::NativeConstruct();
	_ChooseButton = Cast<URPGIntroChooseCharacterButton>(GetWidgetFromName("CharacterButton"));
	_ChooseButton->OnClicked.AddDynamic(this, &URPGIntroLobbySlotInfoLayout::OnClick);
	_BackgroundImage = Cast<UImage>(GetWidgetFromName("BackgroundImage"));
	_LevelText = Cast<UTextBlock>(GetWidgetFromName("LevelText"));
	_JobText = Cast<UTextBlock>(GetWidgetFromName("JobText"));
	_NameText = Cast<UTextBlock>(GetWidgetFromName("NameText"));
}

void URPGIntroLobbySlotInfoLayout::OnClick()
{
	ARPGIntroController* Controller = Cast<ARPGIntroController>(GetWorld()->GetFirstPlayerController());
	Controller->ChangeEmotionAnim(_ScarecrowIndex);
}
