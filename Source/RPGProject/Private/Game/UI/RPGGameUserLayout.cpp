// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameUserLayout.h"
#include "Game/UI/RPGGameInventoryLayout.h"
#include "Game/UI/RPGGameUserInfoLayout.h"

void URPGGameUserLayout::NativeConstruct()
{
	Super::NativeConstruct();

	_UserInfoLayout = Cast<URPGGameUserInfoLayout>(GetWidgetFromName("UserInfoLayout"));
	_InventoryLayout = Cast<URPGGameInventoryLayout>(GetWidgetFromName("InventoryLayout"));

}
