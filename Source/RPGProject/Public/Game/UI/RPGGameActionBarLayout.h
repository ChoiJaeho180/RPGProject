// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Game/RPGGameItemStruct.h"
#include "Game/UI/RPGGameBaseLayout.h"
#include "RPGGameActionBarLayout.generated.h"

class URPGGameActionBarSlot;
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
	TArray<URPGGameActionBarSlot*> _ActionBarSlots;
	UPROPERTY()
	ARPGGameDataCopy* _ChecActonBarSlotData;

public:
	virtual void NativeConstruct() override;
	void NativeTick();
public:
	TSharedPtr<FRPGItemInfo> FindItem(const TSharedPtr<FRPGItemInfo>& KeySlotData, const TArray<TSharedPtr<FRPGItemInfo>>& CharacterItems);
	TSharedPtr<FRPGItemInfo> FindSlotData(const FString& Key);

};
