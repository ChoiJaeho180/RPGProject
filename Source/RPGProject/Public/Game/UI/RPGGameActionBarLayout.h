// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Game/RPGGameItemStruct.h"
#include "Game/UI/RPGGameBaseLayout.h"
#include "RPGGameActionBarLayout.generated.h"

class URPGGameActionBarSlot;
class URPGGameActionBarSkillSlot;
class ARPGGameDataCopy;
class UButton;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameActionBarLayout : public URPGGameBaseLayout
{
	GENERATED_BODY()
private:
	UPROPERTY()
	TArray<URPGGameActionBarSlot*> _ActionBarSlots;
	TArray<URPGGameActionBarSkillSlot*> _ActionBarSkillSlots;
	UPROPERTY()
	ARPGGameDataCopy* _ChecActonBarSlotData;
	
public:
	virtual void NativeConstruct() override;
	void NativeTick();
	void UpdateSkillSlot();
	void UpdatePortionSlot();
public:
	void InitRestActionBar(const TArray<FRPGRestItem>& RestActionBar);
	URPGGameActionBarSkillSlot* FindSkillInfo(const FString& Identify);
	TSharedPtr<FRPGItemInfo> FindItem(const TSharedPtr<FRPGItemInfo>& KeySlotData, const TArray<TSharedPtr<FRPGItemInfo>>& CharacterItems);
	TSharedPtr<FRPGItemInfo> FindSlotData(const FString& Key);
	TArray<TSharedPtr<FRPGItemSlot>> GetValidSlotData();
};
