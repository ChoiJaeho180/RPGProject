// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Game/RPGGameItemStruct.h"
#include "UObject/NoExportTypes.h"
#include "RPGGameUIIdeliver.generated.h"

class URPGGameInventoryLayout;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameUIIdeliver : public UObject
{
	GENERATED_BODY()
private:
	URPGGameInventoryLayout* _TargetUI;
public:
	void InitInventory(const TArray<FRPGRestItem>& NewItem);
	void SetDeliveryTargetUI(URPGGameInventoryLayout* NewUI);
	void SendInputState(const EInventoryUIType& NewInput);
	void ActiveShop();
	TSharedPtr<FRPGItemInfo> GetInputPortionSlotInfo(const FString Key);
};
