// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameBagLayout.h"
#include "Components/UniformGridPanel.h"
#include "Game/UI/RPGGameBagslot.h"
#include "Components/UniformGridSlot.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetTree.h"
#include "Game/UI/RPGGameTitleBarLayout.h"

#define SLOT_COUNT 36
 
void URPGGameBagLayout::NativeConstruct()
{
	Super::NativeConstruct();

	_TitleBarLayout = Cast<URPGGameTitleBarLayout>(GetWidgetFromName("InventoryTitleBarLayout"));
	_TitleBarLayout->delegateTitleDragAndDrop.BindUObject(this, &URPGGameBagLayout::SetPosition);

	_BagGridPanel = Cast<UUniformGridPanel>(GetWidgetFromName("InventoryGridPanel"));
	_GoldText = Cast<UTextBlock>(GetWidgetFromName("GoldText"));

	FString DefaultSlotName = "InventorySlot_";
	for(int i = 0; i < SLOT_COUNT; i++)
	{
		FString SlotName =  DefaultSlotName + FString::FromInt(i);
		URPGGameBagslot* NewSlot = Cast<URPGGameBagslot>(GetWidgetFromName(*SlotName));
		_BagSlots.Add(NewSlot);
	}
	Visibility = ESlateVisibility::Visible;
}

void URPGGameBagLayout::SetPosition(const FVector2D& NewPosition)
{
	SetPositionInViewport(NewPosition, false);
}

