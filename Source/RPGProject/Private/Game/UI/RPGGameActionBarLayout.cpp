// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameActionBarLayout.h"
#include "Game/UI/RPGGameActionBarSlot.h"
#include "Common/RPGCommonGameInstance.h"
#include "Game/RPGGameDataCopy.h"

#define PORTION_START_INDEX 8

void URPGGameActionBarLayout::NativeConstruct()
{
	Super::NativeConstruct();

	TArray<FString> SlotNames = { "Slot_Q", "Slot_W", "Slot_E", "Slot_R",
								 "Slot_A", "Slot_S", "Slot_D", "Slot_F",
								"Slot_1", "Slot_2", "Slot_3", "Slot_4", 
								"Slot_5", "Slot_6", "Slot_7", "Slot_8", };

	for (int i = 0; i < SlotNames.Num(); i++)
	{
		EItemIsFrom NewState = i / (SlotNames.Num() / 2) == 0 ? EItemIsFrom::LEFT_HOT_BAR : EItemIsFrom::RIGHT_HOT_BAR;
		URPGGameActionBarSlot* NewSlot = Cast<URPGGameActionBarSlot>(GetWidgetFromName(*SlotNames[i]));
		TSharedPtr<FRPGItemSlot> NewData = MakeShareable(new FRPGItemSlot);
		FString lhs, rhs;
		SlotNames[i].Split("_", &lhs, &rhs);
		NewSlot->SetKeyText(rhs);
		NewSlot->SetItemIsFrom(NewState);
		NewSlot->SetItemSlotData(NewData);
		_ActionBarSlots.Add(NewSlot);
	}

	URPGCommonGameInstance* GI = Cast<URPGCommonGameInstance>(GetGameInstance());
	_ChecActonBarSlotData = GI->GetDataCopyClass();
}

void URPGGameActionBarLayout::NativeTick()
{
	auto CharacterItems = _ChecActonBarSlotData->GetCharacterItemsInfo();
	for (int i = PORTION_START_INDEX; i < _ActionBarSlots.Num(); i++)
	{
		auto SlotData = _ActionBarSlots[i]->GetItemSlotData();
		if (SlotData->Name == FName("None"))
			continue;

		auto FindItemData = FindItem(SlotData, CharacterItems);
		if (FindItemData == nullptr)
		{
			if(FindItemData->Name != FName("None"))
				_ActionBarSlots[i]->UpdateNullItem();
		}
		else
		{
			if (SlotData->TimeStamp == FindItemData->TimeStamp)
				continue;
			_ActionBarSlots[i]->UpdateItem(FindItemData);
		}
	}
}

TSharedPtr<FRPGItemInfo> URPGGameActionBarLayout::FindItem(const TSharedPtr<FRPGItemInfo>& KeySlotData, const TArray<TSharedPtr<FRPGItemInfo>>& CharacterItems)
{
	for (int i = 0; i < CharacterItems.Num(); i++)
	{
		if (KeySlotData->Name == CharacterItems[i]->Name)
		{
			return CharacterItems[i];
		}
	}
	return nullptr;
}

