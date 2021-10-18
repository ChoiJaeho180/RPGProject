// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameActionBarLayout.h"
#include "Game/UI/RPGGameActionBarSlot.h"
#include "Common/RPGCommonGameInstance.h"
#include "Game/RPGGameDataCopy.h"
#include "Game/UI/RPGGameActionBarSkillSlot.h"
#include "Game/RPGGameDataTableManager.h"

void URPGGameActionBarLayout::NativeConstruct()
{
	Super::NativeConstruct();

	TArray<FString> SlotSkillNames = {
								"Slot_Q", "Slot_W", "Slot_E", "Slot_R",
								"Slot_A", "Slot_S", "Slot_D", "Slot_F", };
	for (int i = 0; i < SlotSkillNames.Num(); i++)
	{
		URPGGameActionBarSkillSlot* NewSlot = Cast<URPGGameActionBarSkillSlot>(GetWidgetFromName(*SlotSkillNames[i]));
		FString lhs, rhs;
		SlotSkillNames[i].Split("_", &lhs, &rhs);
		NewSlot->SetKeyText(rhs);
		_ActionBarSkillSlots.Add(NewSlot);
	}
	URPGGameDataTableManager* DTManager = Cast<URPGCommonGameInstance>(GetGameInstance())->GetDataTableManager();
	_ActionBarSkillSlots[0]->SetIcon(DTManager->GetSkillNameToData("Cut the Ground")->Image);
	_ActionBarSkillSlots[1]->SetIcon(DTManager->GetSkillNameToData("Hack the Earth")->Image);

	TArray<FString> SlotNames = { 
								"Slot_1", "Slot_2", "Slot_3", "Slot_4", 
								"Slot_5", "Slot_6", "Slot_7", "Slot_8", };

	for (int i = 0; i < SlotNames.Num(); i++)
	{
		EItemIsFrom NewState = i / (SlotNames.Num() / 2) == 0 ? EItemIsFrom::LEFT_HOT_BAR : EItemIsFrom::RIGHT_HOT_BAR;
		URPGGameActionBarSlot* NewSlot = Cast<URPGGameActionBarSlot>(GetWidgetFromName(*SlotNames[i]));
		TSharedPtr<FRPGItemSlot> NewData = MakeShareable(new FRPGItemSlot);
		NewData->SlotIndex = i;
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
	if (_ChecActonBarSlotData->GetbInitFirstItem() == false) return;
	UpdatePortionSlot();
	UpdateSkillSlot();
}

void URPGGameActionBarLayout::UpdateSkillSlot()
{
	auto SkillInfo = _ChecActonBarSlotData->GetSkillCoolDownInfo();
	for (int i = 0; i < SkillInfo.Num(); i++)
	{
		auto result = FindSkillInfo(SkillInfo[i]->Identify);
		if (result == nullptr) continue;
		result->Update(SkillInfo[i]);
	}
}

void URPGGameActionBarLayout::UpdatePortionSlot()
{
	auto CharacterItems = _ChecActonBarSlotData->GetCharacterItemsInfo();

	for (int i = 0; i < _ActionBarSlots.Num(); i++)
	{
		auto SlotData = _ActionBarSlots[i]->GetItemSlotData();
		if (SlotData->Name == FName("None")) continue;

		auto FindItemData = FindItem(SlotData, CharacterItems);
		if (FindItemData == nullptr)
		{
			if (SlotData->Name != FName("None"))
			{
				_ActionBarSlots[i]->UpdateNullItem();
			}
		}
		else
		{
			if (SlotData->TimeStamp == FindItemData->TimeStamp) continue;

			_ActionBarSlots[i]->UpdateItem(FindItemData);
		}
	}
}

void URPGGameActionBarLayout::InitRestActionBar(const TArray<FRPGRestItem>& RestActionBar)
{
	UE_LOG(LogTemp, Warning, TEXT("URPGGameActionBarLayout : %d"), RestActionBar.Num());
	for (int i = 0; i < RestActionBar.Num(); i++)
	{
		((URPGGameActionBarSlot*)_ActionBarSlots[RestActionBar[i].SlotIndex])->Init(RestActionBar[i].SlotIndex, RestActionBar[i].Name,  RestActionBar[i].Count);
	}
}

URPGGameActionBarSkillSlot* URPGGameActionBarLayout::FindSkillInfo(const FString& Identify)
{
	for (int i = 0; i < _ActionBarSkillSlots.Num(); i++)
	{
		if (_ActionBarSkillSlots[i]->GetKeyText() == Identify) return _ActionBarSkillSlots[i];
	}
	return nullptr;
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

TSharedPtr<FRPGItemInfo> URPGGameActionBarLayout::FindSlotData(const FString& Key)
{
	for (int i = 0; i < _ActionBarSlots.Num(); i++)
	{
		if (Key != _ActionBarSlots[i]->GetKeyText())
			continue;
		
		return _ActionBarSlots[i]->GetItemSlotData();
	}
	return nullptr;
}

TArray<TSharedPtr<FRPGItemSlot>> URPGGameActionBarLayout::GetValidSlotData()
{
	TArray<TSharedPtr<FRPGItemSlot>> Data;
	for (int i = 0; i < _ActionBarSlots.Num(); i++)
	{
		if (_ActionBarSlots[i]->GetItemImage() == nullptr)
			continue;
		Data.Add(_ActionBarSlots[i]->GetItemSlotData());
	}
	return Data;
}

