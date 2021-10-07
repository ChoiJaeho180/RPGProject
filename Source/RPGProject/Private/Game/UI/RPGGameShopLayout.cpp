// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameShopLayout.h"
#include "Game/UI/RPGGameBagLayout.h"
#include "Game/UI/RPGGameShopBagLayout.h"

void URPGGameShopLayout::NativeConstruct()
{
	Super::NativeConstruct();

	_ShopBagLayout = Cast<URPGGameShopBagLayout>(GetWidgetFromName("ShopBagLayout"));
	_ShopBagLayout->delegateCloseLayout.BindUObject(this, &URPGGameShopLayout::CloseButton);
}

void URPGGameShopLayout::SetBagLayout(URPGGameBagLayout* BagLayout)
{
	_BagLayout = BagLayout;
}

void URPGGameShopLayout::CloseButton()
{
	SetVisibility(ESlateVisibility::Hidden);
	_BagLayout->SetVisibility(ESlateVisibility::Hidden);
}
