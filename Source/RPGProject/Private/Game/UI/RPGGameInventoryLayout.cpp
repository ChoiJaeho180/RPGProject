// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameInventoryLayout.h"
#include "Game/UI/RPGGameBagLayout.h"
#include "Game/UI/RPGGameEquipmentLayout.h"
#include "Game/UI/RPGGameTitleDragAndDrop.h"
#include "Game/UI/RPGGameActionBarLayout.h"
#include "Game/UI/RPGGameShopLayout.h"
#include "Game/UI/RPGGameQuestQuickLayout.h"
#include "Game/UI/RPGGameStatLayout.h"

void URPGGameInventoryLayout::NativeConstruct()
{
	Super::NativeConstruct();

	_BagLayout = Cast<URPGGameBagLayout>(GetWidgetFromName("Bag"));
	_BagLayout->Visibility = ESlateVisibility::Visible;
	_EquipmentLayout = Cast<URPGGameEquipmentLayout>(GetWidgetFromName("Equipment"));
	_ActionBar = Cast<URPGGameActionBarLayout>(GetWidgetFromName("ActionBar"));
	_ShopLayout = Cast<URPGGameShopLayout>(GetWidgetFromName("ShopLayout"));
	_ShopLayout->SetVisibility(ESlateVisibility::Hidden);
	_ShopLayout->SetBagLayout(_BagLayout);

	_QuestQuickLayout = Cast<URPGGameQuestQuickLayout>(GetWidgetFromName("QuestQuickLayout"));
	_QuestQuickLayout->SetVisibility(ESlateVisibility::Hidden);
	_StatLayout = Cast<URPGGameStatLayout>(GetWidgetFromName("GameStat"));
	_StatLayout->SetVisibility(ESlateVisibility::Hidden);

}

void URPGGameInventoryLayout::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	_DeltaTime += InDeltaTime;
	if (_DeltaTime < STARNDARD_TIME)
		return;

	if (_ActionBar != nullptr)
	{
		_ActionBar->NativeTick();
	}

	_QuestQuickLayout->Tick();
	
	if (_StatLayout->GetVisibility() == ESlateVisibility::Visible)
	{
		_StatLayout->Tick();
	}

	if (_BagLayout->GetVisibility() == ESlateVisibility::Visible)
	{
		_BagLayout->NativeTick(MyGeometry, InDeltaTime);
	}
	_DeltaTime = 0.f; 
}


bool URPGGameInventoryLayout::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	URPGGameTitleDragAndDrop* Widget = Cast<URPGGameTitleDragAndDrop>(InOperation);
	if (Widget == nullptr)
		return false;

	Widget->GetParentWidget()->AddToViewport();

	FVector2D NewPosition = InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition()) - Widget->GetMouseOffset();
	Widget->GetParentWidget()->SetPositionInViewport(NewPosition, false);
	return true;
}

void URPGGameInventoryLayout::UpdateVisibility(const EInventoryUIType& NewInput)
{
	UUserWidget* TempWidget = nullptr;
	switch (NewInput)
	{
		case EInventoryUIType::BAG_INVENTORY:
			TempWidget = _BagLayout;
			break;
		case EInventoryUIType::EQUIPMENT_INVENTORY:
			TempWidget = _EquipmentLayout;
			break;
		case EInventoryUIType::STAT_INVENTORY:
			TempWidget = _StatLayout;
			break;
	}

	if (TempWidget == nullptr)
		return;

	ESlateVisibility NewState = TempWidget->GetVisibility() == ESlateVisibility::Visible ? ESlateVisibility::Hidden : ESlateVisibility::Visible;
	TempWidget->SetVisibility(NewState);
	UE_LOG(LogTemp, Warning, TEXT("UpdateVisibility"));
}

URPGGameActionBarLayout* URPGGameInventoryLayout::GetActionBar()
{
	return _ActionBar;
}

TArray<TSharedPtr<FRPGItemSlot>> URPGGameInventoryLayout::GetVaildBagData()
{
	return _BagLayout->GetValidSlotData();
}

TArray<TSharedPtr<FRPGItemSlot>> URPGGameInventoryLayout::GetVaildActionBarData()
{
	return _ActionBar->GetValidSlotData();
}

void URPGGameInventoryLayout::InitInventory(const TArray<FRPGRestItem>& RestItemData)
{
	_BagLayout->InitBagSlots(RestItemData);
}

void URPGGameInventoryLayout::InitActionBar(const TArray<FRPGRestItem>& RestActionBar)
{
	_ActionBar->InitRestActionBar(RestActionBar);
}

void URPGGameInventoryLayout::ActiveShop()
{
	_ShopLayout->SetVisibility(ESlateVisibility::Visible);
	_BagLayout->RemoveFromParent();
	_BagLayout->AddToViewport(10);
	_BagLayout->SetVisibility(ESlateVisibility::Visible);
	_BagLayout->SetPositionInViewport(FVector2D(600, 200));
}

void URPGGameInventoryLayout::ActiveQuestQuick()
{
	_QuestQuickLayout->SetVisibility(ESlateVisibility::Visible);
}

