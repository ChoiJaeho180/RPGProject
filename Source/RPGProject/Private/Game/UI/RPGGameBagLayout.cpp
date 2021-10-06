// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameBagLayout.h"
#include "Components/UniformGridPanel.h"
#include "Game/UI/RPGGameBagslot.h"
#include "Components/UniformGridSlot.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetTree.h"
#include "Game/UI/RPGGameTitleBarLayout.h"
#include "Common/RPGCommonGameInstance.h"
#include "Game/RPGGameDataCopy.h"
#include "Game/UI/RPGGameSlotDragDropOperation.h"
#include "Game/UI/RPGGameSlotDragDropBaseLayout.h"

#define SLOT_COUNT 36

void URPGGameBagLayout::NativeConstruct()
{
	Super::NativeConstruct();

	_TitleBarLayout = Cast<URPGGameTitleBarLayout>(GetWidgetFromName("InventoryTitleBarLayout"));
	_TitleBarLayout->SetParentWidget(this);
	_BagGridPanel = Cast<UUniformGridPanel>(GetWidgetFromName("InventoryGridPanel"));
	_GoldText = Cast<UTextBlock>(GetWidgetFromName("GoldText"));

	FString DefaultSlotName = "InventorySlot_";
	for(int i = 0; i < SLOT_COUNT; i++)
	{
		FString SlotName =  DefaultSlotName + FString::FromInt(i);
		URPGGameBagslot* NewSlot = Cast<URPGGameBagslot>(GetWidgetFromName(*SlotName));
		TSharedPtr<FRPGItemSlot> NewData = MakeShareable(new FRPGItemSlot);
		NewData->SlotIndex = i;
		NewSlot->ActiveSlot(ESlateVisibility::Hidden);
		NewSlot->SetItemIsFrom(EItemIsFrom::BAG);
		//NewSlot->SetParent(this);
		NewSlot->SetItemSlotData(NewData);
		_SlotData.Add(NewSlot);
		//_BagSlots.Add(NewSlot);
	}

	URPGCommonGameInstance* GI = Cast<URPGCommonGameInstance>(GetGameInstance());
	_CheckBagSlotData = GI->GetDataCopyClass();

}

void URPGGameBagLayout::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (_bRestInit == false)
		return;
	TArray<TSharedPtr<FRPGItemInfo>> NewItemsInfo = _CheckBagSlotData->GetCharacterItemsInfo();
	for (int i = 0; i < NewItemsInfo.Num(); i++)
	{
		URPGGameBagslot* Find = FindItem(NewItemsInfo[i]);
		if (Find == nullptr)
			continue;

		Find->UpdateItem(NewItemsInfo[i]);
	}
	
	for (int i = 0; i < _SlotData.Num(); i++)
	{
		TSharedPtr<FRPGItemInfo> SlotData = FindItem(_SlotData[i]->GetItemSlotData(), NewItemsInfo);
		if (SlotData == nullptr)
		{
			if(_SlotData[i]->GetItemSlotData()->Name != FName("None"))
				_SlotData[i]->UpdateNullItem();
		}
	}
	
}

void URPGGameBagLayout::InitBagSlots(const TArray<FRPGRestItem>& RestItemData)
{
	for (int i = 0; i < RestItemData.Num(); i++)
	{
		((URPGGameBagslot*)_SlotData[RestItemData[i].SlotIndex])->Init(RestItemData[i].Name, RestItemData[i].SlotIndex, RestItemData[i].Count);
	}
	_bRestInit = true;
}

TSharedPtr<FRPGItemInfo> URPGGameBagLayout::FindItem(const TSharedPtr<FRPGItemInfo>& NewItem, const TArray<TSharedPtr<FRPGItemInfo>>& NewItemsInfo)
{
	for (int i = 0; i < NewItemsInfo.Num(); i++)
	{
		if (NewItemsInfo[i]->Name == NewItem->Name)
		{
			return NewItemsInfo[i];
		}
	}
	return nullptr;
}

URPGGameBagslot* URPGGameBagLayout::FindItem(const TSharedPtr<FRPGItemInfo>& NewItem)
{
	for (int i = 0; i < _SlotData.Num(); i++)
	{
		if (_SlotData[i]->GetItemSlotData()->Name == NewItem->Name)
		{
			return _SlotData[i];
		}
	}
	return nullptr;
}


