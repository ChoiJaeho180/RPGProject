// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/UI/RPGGameSlotDragDropOperation.h"

void URPGGameSlotDragDropOperation::ExChangeSlot(IRPGGameDataSlots* From, IRPGGameDataSlots* To, int FromIndex, int ToIndex)
{
	TWeakPtr<FRPGItemSlot> FromTemp = From->SlotData[FromIndex]->GetItemSlotData();
	TWeakPtr<FRPGItemSlot> ToTemp = To->SlotData[ToIndex]->GetItemSlotData();
	From->SlotData[FromIndex]->SetItemSlotData(ToTemp.Pin());
	To->SlotData[ToIndex]->SetItemSlotData(FromTemp.Pin());

	From->SlotData[FromIndex]->SetItemSlotIndex(FromIndex);
	To->SlotData[ToIndex]->SetItemSlotIndex(ToIndex);

	From->SlotData[FromIndex]->UpdateUI();
	To->SlotData[ToIndex]->UpdateUI();
}
