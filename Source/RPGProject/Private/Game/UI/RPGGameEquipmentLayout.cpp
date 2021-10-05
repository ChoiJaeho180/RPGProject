// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameEquipmentLayout.h"
#include "Game/UI/RPGGameTitleBarLayout.h"

void URPGGameEquipmentLayout::NativeConstruct()
{
	Super::NativeConstruct();
	_TitleBarLayout = Cast<URPGGameTitleBarLayout>(GetWidgetFromName("InventoryTitleBarLayout"));
	_TitleBarLayout->SetParentWidget(this);
	_TitleBarLayout->SetText("Equipment");
}
