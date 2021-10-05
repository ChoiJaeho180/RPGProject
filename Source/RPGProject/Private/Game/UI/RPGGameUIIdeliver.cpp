// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameUIIdeliver.h"
#include "Game/UI/RPGGameInventoryLayout.h"

void URPGGameUIIdeliver::InitInventory(const TArray<FRPGRestItem>& NewItem)
{
	_TargetUI->InitInventory(NewItem);
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
