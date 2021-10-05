// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameBagslot.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Common/RPGCommonGameInstance.h"
#include "Game/RPGGameDataTableManager.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Game/UI/RPGGameSlotDragDropOperation.h"
#include "Components/TextBlock.h"

bool URPGGameBagslot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	URPGGameSlotDragDropOperation* ItemOperation = Cast<URPGGameSlotDragDropOperation>(InOperation);
	if (IsValid(ItemOperation) == true)
	{
		EItemIsFrom ItemIsFrom = ItemOperation->GetItemIsFrom();

		if (_ItemIsFrom == ItemIsFrom)
		{
			ItemOperation->ExChangeSlot(ItemOperation->InventorySlotUI->GetSlotParent(), _Parent, ItemOperation->InventorySlotUI->GetItemSlotData()->SlotIndex, _ItemInfo->SlotIndex);
		}
		else if (_ItemIsFrom == EItemIsFrom::BAG && ItemIsFrom == EItemIsFrom::EQUIP)
		{

		}
		else if (_ItemIsFrom == EItemIsFrom::BAG && ItemIsFrom == EItemIsFrom::HOT_BAR)
		{

		}

		InOperation = Cast<UDragDropOperation>(ItemOperation);
	}
	
	UUserWidget::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	return true;
}

void URPGGameBagslot::NativeConstruct()
{
	Super::NativeConstruct();
	_Button = Cast<UButton>(GetWidgetFromName("IconButton"));
	_Icon = Cast<UImage>(GetWidgetFromName("IconImage"));
	_AmountText = Cast<UTextBlock>(GetWidgetFromName("Amount"));
	//ActiveSlot(ESlateVisibility::Hidden);
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

	if (_ItemInfo->Count == 0)
		_AmountText->SetText(FText::FromString(""));
	else
		_AmountText->SetText(FText::AsNumber(_ItemInfo->Count));

	_Icon->SetBrushFromTexture(_ItemInfo->Image);
	UE_LOG(LogTemp, Warning, TEXT("UpdateUI"));
}

void URPGGameBagslot::UpdateItem(TSharedPtr<FRPGItemInfo>& NewItemInfo)
{
	if (_ItemInfo->TimeStamp == NewItemInfo->TimeStamp)
		return;

	_ItemInfo->SetInfo(NewItemInfo);
	URPGCommonGameInstance* GI = Cast<URPGCommonGameInstance>(GetGameInstance());
	URPGGameDataTableManager* DT = GI->GetDataTableManager();
	
	_Icon->SetBrushFromTexture(DT->GetNameToTexture(_ItemInfo->Name));
	UE_LOG(LogTemp, Warning, TEXT("asds"));
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
	//ActiveSlot(ESlateVisibility::SelfHitTestInvisible);
}

void URPGGameBagslot::SetItem()
{
	_Icon->SetBrushFromTexture(_ItemInfo->Image);
}
