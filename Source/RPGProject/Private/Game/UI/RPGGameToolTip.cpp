// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameToolTip.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void URPGGameToolTip::NativeConstruct()
{
	Super::NativeConstruct();

	_ToolTipImage = Cast<UImage>(GetWidgetFromName("ToolTipImage"));
	_Name = Cast<UTextBlock>(GetWidgetFromName("Name"));
	_DescriptionText = Cast<UTextBlock>(GetWidgetFromName("DescriptionText"));
	_GoldText = Cast<UTextBlock>(GetWidgetFromName("GoldText"));

	_ToolTipImage->SetBrushFromTexture(_StoreImage);
	_Name->SetText(_StoreName);
	_DescriptionText->SetText(_StoreDesription);
	_GoldText->SetText(_Gold);
}

void URPGGameToolTip::SetInfo(UTexture2D* Texture, FText Name, FText Description, FText Gold)
{
	_StoreImage = Texture;
	_StoreName = Name;
	_StoreDesription = Description;
	_Gold = Gold;
}
