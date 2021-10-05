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
		NewSlot->SetParent(this);
		NewSlot->SetItemSlotData(NewData);
		SlotData.Add(NewSlot);
		//_BagSlots.Add(NewSlot);
	}

	URPGCommonGameInstance* GI = Cast<URPGCommonGameInstance>(GetGameInstance());
	_CheckBagSlotData = GI->GetDataCopyClass();

}

void URPGGameBagLayout::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	_DeltaTime += InDeltaTime;
	if (_DeltaTime < STARNDARD_TIME)
		return;
	TArray<TSharedPtr<FRPGItemInfo>> NewItemsInfo = _CheckBagSlotData->GetCharacterItemsInfo();
	//for (int i = 0; i < NewItemsInfo.Num(); i++)
	{
		//_BagSlots[0]->UpdateItem(NewItemsInfo[0]);
	}
	_DeltaTime = 0.f;
}

void URPGGameBagLayout::InitBagSlots(const TArray<FRPGRestItem>& RestItemData)
{
	for (int i = 0; i < RestItemData.Num(); i++)
	{
		((URPGGameBagslot*)SlotData[RestItemData[i].SlotIndex])->Init(RestItemData[i].Name, RestItemData[i].SlotIndex, RestItemData[i].Count);
	}
}

bool URPGGameBagLayout::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	URPGGameSlotDragDropOperation* Widget = Cast<URPGGameSlotDragDropOperation>(InOperation);
	if (Widget == nullptr)
		return false;

//	Widget->GetParentWidget()->AddToViewport();

	//FVector2D NewPosition = InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition()) - Widget->GetMouseOffset();
	//Widget->GetParentWidget()->SetPositionInViewport(NewPosition, false);
	return true;
}
