// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameActionBarSlot.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Game/UI/RPGGameSlotDragDropOperation.h"
#include "Components/Image.h"
#include "Components/Border.h"
#include "Game/UI/RPGGameTitleDragAndDrop.h"
#include "Common/RPGCommonGameInstance.h"
#include "Game/RPGGameDataTableManager.h"

void URPGGameActionBarSlot::NativeConstruct()
{
	Super::NativeConstruct();

	_KeyText = Cast<UTextBlock>(GetWidgetFromName("KeyText"));
	_IconBorder = Cast<UBorder>(GetWidgetFromName("IconBorder"));
	_CooldownBorder = Cast<UBorder>(GetWidgetFromName("CooldownBorder"));
	_AmountText = Cast<UTextBlock>(GetWidgetFromName("AmountText"));
	Visibility = ESlateVisibility::Visible;


}


bool URPGGameActionBarSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	URPGGameSlotDragDropOperation* ItemOperation = Cast<URPGGameSlotDragDropOperation>(InOperation);
	if (ItemOperation == nullptr)
	{
		URPGGameTitleDragAndDrop* TitleBarOper = Cast<URPGGameTitleDragAndDrop>(InOperation);
		TitleBarOper->CorrectPosition(InGeometry, InDragDropEvent);
		return true;
	}

	UE_LOG(LogTemp, Warning, TEXT("URPGGameActionBarSlot::NativeOnDrop"));
	if (IsValid(ItemOperation) == true)
	{
		EItemIsFrom ItemIsFrom = ItemOperation->GetItemIsFrom();
		if (_ItemIsFrom == ItemIsFrom)
		{
			ItemOperation->ExChangeSlot(ItemOperation->InventorySlotUI, this);
		}
		else if (_ItemIsFrom == EItemIsFrom::RIGHT_HOT_BAR && ItemIsFrom == EItemIsFrom::BAG)
		{
			TSharedPtr<FRPGItemSlot> ItemInfo = ItemOperation->InventorySlotUI->GetItemSlotData();
			if (ItemInfo->InventoryType == EInventoryType::CONSUMPTION_INVENTORY)
			{
				ItemOperation->AddSlot(ItemOperation->InventorySlotUI, this);
			}
		}
	}

	UUserWidget::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	return true;
}

void URPGGameActionBarSlot::ActiveSlot(ESlateVisibility NewState)
{
	_IconBorder->SetVisibility(NewState);
}

void URPGGameActionBarSlot::UpdateUI()
{
	if (_ItemInfo->Image == nullptr)
		ActiveSlot(ESlateVisibility::Hidden);
	else
		ActiveSlot(ESlateVisibility::SelfHitTestInvisible);

	if (_ItemInfo->Count == -1)
		_AmountText->SetText(FText::FromString(""));
	else
		_AmountText->SetText(FText::AsNumber(_ItemInfo->Count));

	_IconBorder->SetBrushFromTexture(_ItemInfo->Image);
}

void URPGGameActionBarSlot::Init(int SlotIndex, FName Name, int Count)
{
	_ItemInfo = MakeShareable(new FRPGItemSlot);

	URPGCommonGameInstance* GI = Cast<URPGCommonGameInstance>(GetGameInstance());
	URPGGameDataTableManager* DT = GI->GetDataTableManager();
	FGameItemType* ItemType = DT->GetNameToData(Name);
	_ItemInfo->SetInfo(Count, ItemType->Price, ItemType->Description, Name, ItemType->InventoryType, 0);
	_ItemInfo->SetInfo(ItemType->Image, SlotIndex);
	UpdateUI();
}

void URPGGameActionBarSlot::UpdateNullItem()
{
	_ItemInfo->Image = nullptr;
	_ItemInfo->Count = -1;
	_ItemInfo->TimeStamp = 0;
	UpdateUI();
}

void URPGGameActionBarSlot::UpdateItem(const TSharedPtr<FRPGItemInfo> KeySlotData)
{
	_ItemInfo->Count = KeySlotData->Count;
	_ItemInfo->TimeStamp = KeySlotData->TimeStamp;
	UpdateUI();
}


URPGGameSlotDragDropBaseLayout* URPGGameActionBarSlot::GetDragObject()
{
	URPGCommonGameInstance* GI = Cast<URPGCommonGameInstance>(GetGameInstance());
	URPGGameActionBarSlot* DraggedItem = CreateWidget<URPGGameActionBarSlot>(GetWorld(), GI->RPGActionBarSlotClass);
	DraggedItem->SetRenderScale(FVector2D(0.5f, 0.5f));
	DraggedItem->SetRenderTranslation(FVector2D(-30, -50));
	DraggedItem->_IconBorder = Cast<UBorder>(DraggedItem->GetWidgetFromName("IconBorder"));
	if (DraggedItem->_IconBorder != nullptr)
	{
		DraggedItem->ActiveSlot(ESlateVisibility::SelfHitTestInvisible);
		DraggedItem->_IconBorder->SetBrushFromTexture(GetItemImage());
	}
	return DraggedItem;
}

UTexture2D* URPGGameActionBarSlot::GetItemImage() const
{
	if (_ItemInfo == nullptr)
		return nullptr;

	return _ItemInfo->Image;
}

void URPGGameActionBarSlot::SetKeyText(FString InputKey)
{
	_KeyText->SetText(FText::FromString(InputKey));
}

FString URPGGameActionBarSlot::GetKeyText()
{
	return _KeyText->GetText().ToString();
}
