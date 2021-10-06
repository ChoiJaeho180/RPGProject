// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameBagslot.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Common/RPGCommonGameInstance.h"
#include "Game/RPGGameDataTableManager.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Game/UI/RPGGameSlotDragDropOperation.h"
#include "Components/TextBlock.h"

void URPGGameBagslot::NativeConstruct()
{
	Super::NativeConstruct();
	_Button = Cast<UButton>(GetWidgetFromName("IconButton"));
	_Icon = Cast<UImage>(GetWidgetFromName("IconImage"));
	_AmountText = Cast<UTextBlock>(GetWidgetFromName("Amount"));
	_Background = Cast<UImage>(GetWidgetFromName("Background"));

}

bool URPGGameBagslot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	URPGGameSlotDragDropOperation* ItemOperation = Cast<URPGGameSlotDragDropOperation>(InOperation);
	if (IsValid(ItemOperation) == true)
	{
		EItemIsFrom ItemIsFrom = ItemOperation->GetItemIsFrom();

		if (_ItemIsFrom == ItemIsFrom)
		{
			ItemOperation->ExChangeSlot(ItemOperation->InventorySlotUI, this);
		}
		else if (_ItemIsFrom == EItemIsFrom::BAG && ItemIsFrom == EItemIsFrom::EQUIP)
		{
			
		}
		else if (_ItemIsFrom == EItemIsFrom::BAG && ItemIsFrom == EItemIsFrom::LEFT_HOT_BAR)
		{

		}

		InOperation = Cast<UDragDropOperation>(ItemOperation);
	}
	
	UUserWidget::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	return true;
}



UTexture2D* URPGGameBagslot::GetItemImage() const
{
	if (_ItemInfo == nullptr)
		return nullptr;
	
	return _ItemInfo->Image;
}

void URPGGameBagslot::UpdateUI()
{
	if (_ItemInfo->Image == nullptr)
		ActiveSlot(ESlateVisibility::Hidden);
	else
		ActiveSlot(ESlateVisibility::SelfHitTestInvisible);

	if (_ItemInfo->Count == -1)
		_AmountText->SetText(FText::FromString(""));
	else
		_AmountText->SetText(FText::AsNumber(_ItemInfo->Count));

	_Icon->SetBrushFromTexture(_ItemInfo->Image);
}

void URPGGameBagslot::UpdateNullItem()
{
	_ItemInfo->SetEmpty();
	UpdateUI();
}

void URPGGameBagslot::ActiveSlot(ESlateVisibility NewState)
{
	_Button->SetVisibility(NewState);
	_Icon->SetVisibility(NewState);
}

URPGGameSlotDragDropBaseLayout* URPGGameBagslot::GetDragObject()
{
	URPGCommonGameInstance* GI = Cast<URPGCommonGameInstance>(GetGameInstance());
	URPGGameBagslot* DraggedItem = CreateWidget<URPGGameBagslot>(GetWorld(), GI->RPGSlotClass);
	DraggedItem->_Icon = Cast<UImage>(DraggedItem->GetWidgetFromName("IconImage"));
	DraggedItem->_Button = Cast<UButton>(DraggedItem->GetWidgetFromName("IconButton"));
	if (DraggedItem->_Icon != nullptr)
	{
		DraggedItem->ActiveSlot(ESlateVisibility::SelfHitTestInvisible);
		DraggedItem->_Icon->SetBrushFromTexture(GetItemImage());
	}
	return DraggedItem;
}

void URPGGameBagslot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	UUserWidget::NativeOnMouseEnter(InGeometry, InMouseEvent);
	UE_LOG(LogTemp, Warning, TEXT("NativeOnMouseEnter"));
	FLinearColor c;
	_Background->SetColorAndOpacity(c.Blue);
}

void URPGGameBagslot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	UUserWidget::NativeOnMouseLeave(InMouseEvent);
	UE_LOG(LogTemp, Warning, TEXT("NativeOnMouseLeave"));
	FLinearColor c;
	_Background->SetColorAndOpacity(c.White);
}


void URPGGameBagslot::UpdateItem(TSharedPtr<FRPGItemInfo>& NewItemInfo)
{
	if (_ItemInfo->TimeStamp == NewItemInfo->TimeStamp)
		return;

	_ItemInfo->SetInfo(NewItemInfo);

	UpdateUI();
}

void URPGGameBagslot::Init(const FName& Name, const int& SlotIndex, const int& Count)
{
	_ItemInfo = MakeShareable(new FRPGItemSlot);

	URPGCommonGameInstance* GI = Cast<URPGCommonGameInstance>(GetGameInstance());
	URPGGameDataTableManager* DT = GI->GetDataTableManager();
	FGameItemType* ItemType = DT->GetNameToData(Name);
	_ItemInfo->SetInfo(Count, ItemType->Price, ItemType->Description, Name, ItemType->InventoryType,0);
	_ItemInfo->SetInfo(ItemType->Image, SlotIndex);
	UpdateUI();
}

void URPGGameBagslot::SetItem()
{
	_Icon->SetBrushFromTexture(_ItemInfo->Image);
}
