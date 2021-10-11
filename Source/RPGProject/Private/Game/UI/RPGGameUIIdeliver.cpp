// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameUIIdeliver.h"
#include "Game/UI/RPGGameInventoryLayout.h"
#include "Game/UI/RPGGameActionBarLayout.h"

void URPGGameUIIdeliver::InitInventoryAndActionBar(const TArray<FRPGRestItem>& NewItem, const TArray<FRPGRestItem>& ActionBar)
{
	_TargetUI->InitInventory(NewItem);
	_TargetUI->InitActionBar(ActionBar);
}

void URPGGameUIIdeliver::SetDeliveryTargetUI(URPGGameInventoryLayout* NewUI)
{
	_TargetUI = NewUI;
}

void URPGGameUIIdeliver::SendInputState(const EInventoryUIType& NewInput)
{
	UE_LOG(LogTemp, Warning, TEXT("SendInputState"));
	_TargetUI->UpdateVisibility(NewInput);
}

void URPGGameUIIdeliver::ActiveShop()
{
	_TargetUI->ActiveShop();
}

TSharedPtr<FRPGItemInfo> URPGGameUIIdeliver::GetInputPortionSlotInfo(const FString Key)
{
	URPGGameActionBarLayout* AciontBar = _TargetUI->GetActionBar();
	return AciontBar->FindSlotData(Key);
}
