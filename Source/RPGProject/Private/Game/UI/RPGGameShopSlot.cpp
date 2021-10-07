// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameShopSlot.h"
#include "Components/Button.h"
#include "Components/Image.h"

void URPGGameShopSlot::NativeConstruct()
{
	Super::NativeConstruct();
	_Button = Cast<UButton>(GetWidgetFromName("IconButton"));
	_Icon = Cast<UImage>(GetWidgetFromName("IconImage"));
	_Background = Cast<UImage>(GetWidgetFromName("Background"));

}

void URPGGameShopSlot::ActiveSlot(ESlateVisibility NewState)
{
	_Button->SetVisibility(NewState);
	_Icon->SetVisibility(NewState);
}

void URPGGameShopSlot::UpdateUI()
{
	if (_ItemInfo->Image == nullptr)
		ActiveSlot(ESlateVisibility::Hidden);
	else
		ActiveSlot(ESlateVisibility::SelfHitTestInvisible);

	_Icon->SetBrushFromTexture(_ItemInfo->Image);
}
