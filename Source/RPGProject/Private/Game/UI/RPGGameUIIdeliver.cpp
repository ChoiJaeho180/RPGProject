// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameUIIdeliver.h"
#include "Game/UI/RPGGameInventoryLayout.h"

void URPGGameUIIdeliver::SetDeliveryTargetUI(URPGGameInventoryLayout* NewUI)
{
	_TargetUI = NewUI;
}
