// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameTitleBarLayout.h"
#include "Game/UI/RPGGameBagslot.h"
#include "Game/UI/RPGGameTitleDragAndDrop.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Input/Reply.h"

void URPGGameTitleBarLayout::NativeConstruct()
{
	Super::NativeConstruct();
	Visibility = ESlateVisibility::Visible;

	_TitleBorder = Cast<UBorder>(GetWidgetFromName("TitleBorder"));
	_TitleText = Cast<UTextBlock>(GetWidgetFromName("Title"));
}

void URPGGameTitleBarLayout::SetText(FString NewTitle)
{
	_TitleText->SetText(FText::FromString(NewTitle));
}


