// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameSlotDragDropOperation.h"
#include "Game/UI/RPGGameSlotDragDropBaseLayout.h"

void URPGGameSlotDragDropOperation::ExChangeSlot(URPGGameSlotDragDropBaseLayout* From, URPGGameSlotDragDropBaseLayout* To)
{
	TSharedPtr<FRPGItemSlot> FromTemp = From->GetItemSlotData();
	int FromIndex = FromTemp->SlotIndex;
	TSharedPtr<FRPGItemSlot> ToTemp = To->GetItemSlotData();
	int ToIndex = ToTemp->SlotIndex;
	From->SetItemSlotData(ToTemp);
	To->SetItemSlotData(FromTemp);

	From->SetItemSlotIndex(FromIndex);
	To->SetItemSlotIndex(ToIndex);

	From->UpdateUI();
	To->UpdateUI();
}

void URPGGameSlotDragDropOperation::AddSlot(URPGGameSlotDragDropBaseLayout* From, URPGGameSlotDragDropBaseLayout* To)
{
	TSharedPtr<FRPGItemSlot> FromTemp = From->GetItemSlotData();
	To->GetItemSlotData()->SetInfo(FromTemp);
	To->GetItemSlotData()->Image = FromTemp->Image;
	To->UpdateUI();
}
