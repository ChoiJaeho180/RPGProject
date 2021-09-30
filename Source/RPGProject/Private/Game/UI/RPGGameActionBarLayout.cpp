// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameActionBarLayout.h"
#include "Game/UI/RPGGameActionBarSlot.h"

void URPGGameActionBarLayout::NativeConstruct()
{
	Super::NativeConstruct();

	TArray<FString> SlotNames = { "Slot_Q", "Slot_W", "Slot_E", "Slot_R",
								 "Slot_A", "Slot_S", "Slot_D", "Slot_F",
								"Slot_1", "Slot_2", "Slot_3", "Slot_4", 
								"Slot_5", "Slot_6", "Slot_7", "Slot_8", };

	for (int i = 0; i < SlotNames.Num(); i++)
	{
		URPGGameActionBarSlot* NewSlot = Cast<URPGGameActionBarSlot>(GetWidgetFromName(*SlotNames[i]));
		FString lhs, rhs;
		SlotNames[i].Split("_", &lhs, &rhs);
		NewSlot->SetKeyText(rhs);
		_ActionBarSlots.Add(NewSlot);
	}

}