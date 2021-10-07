// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameShopBagLayout.h"
#include "Components/Button.h"
#include "Game/UI/RPGGameShopSlot.h"
#include "Common/RPGCommonGameInstance.h"
#include "Game/RPGGameDataTableManager.h"
#include "Game/UI/RPGGameShopSellHelperLayout.h"
#include "Game/UI/RPGGameSlotDragDropOperation.h"
#define SLOT_COUNT 36

void URPGGameShopBagLayout::NativeConstruct()
{
	Super::NativeConstruct();
	_CloseButton = Cast<UButton>(GetWidgetFromName("CloseButton"));
	_CloseButton->OnClicked.AddDynamic(this, &URPGGameShopBagLayout::CloseButton);


	FString DefaultSlotName = "Shop_Slot_";
	for (int i = 0; i < SLOT_COUNT; i++)
	{
		FString SlotName = DefaultSlotName + FString::FromInt(i);
		URPGGameShopSlot* NewSlot = Cast<URPGGameShopSlot>(GetWidgetFromName(*SlotName));
		TSharedPtr<FRPGItemSlot> NewData = MakeShareable(new FRPGItemSlot);
		NewData->SlotIndex = i;
		NewSlot->ActiveSlot(ESlateVisibility::Hidden);
		NewSlot->SetItemIsFrom(EItemIsFrom::SHOP);
		NewSlot->SetItemSlotData(NewData);
		_ShopSlotData.Add(NewSlot);
	}

	URPGCommonGameInstance* GI = Cast<URPGCommonGameInstance>(GetWorld()->GetGameInstance());
	URPGGameDataTableManager* DTManager = GI->GetDataTableManager();
	TArray<FGameItemType*> ConsumptionData = DTManager->GetData();
	for (int i = 0; i < ConsumptionData.Num(); i++)
	{
		TSharedPtr<FRPGItemSlot> SlotData = _ShopSlotData[i]->GetItemSlotData();
		SlotData->Description = ConsumptionData[i]->Description;
		SlotData->Image = ConsumptionData[i]->Image;
		SlotData->InventoryType = ConsumptionData[i]->InventoryType;
		SlotData->Name = ConsumptionData[i]->Name;
		_ShopSlotData[i]->UpdateUI();
	}


}

bool URPGGameShopBagLayout::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	URPGGameSlotDragDropOperation* ItemOperation = Cast<URPGGameSlotDragDropOperation>(InOperation);
	if (ItemOperation == nullptr)
		return false;
	TSharedPtr<FRPGItemSlot> SellItem = ItemOperation->InventorySlotUI->GetItemSlotData();
	EItemIsFrom ItemFrom = ItemOperation->InventorySlotUI->GetItemIsFrom();
	if (ItemFrom != EItemIsFrom::BAG)
		return false;

	URPGCommonGameInstance* GI = Cast<URPGCommonGameInstance>(GetWorld()->GetGameInstance());
	URPGGameShopSellHelperLayout* SellHelperLayout = CreateWidget<URPGGameShopSellHelperLayout>(GetWorld(), GI->RPGSellHelperClass);
	SellHelperLayout->AddToViewport(11);
	SellHelperLayout->SetUnitPrice(SellItem->Price);
	SellHelperLayout->SetMaxCount(SellItem->Count);
	SellHelperLayout->SetSellName(SellItem->Name);
	SellHelperLayout->SetPositionInViewport(FVector2D(434, 240));
	return true;
}

void URPGGameShopBagLayout::CloseButton()
{
	delegateCloseLayout.ExecuteIfBound();
}

