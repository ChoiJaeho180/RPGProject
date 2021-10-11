// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameUserLayout.h"
#include "Game/UI/RPGGameInventoryLayout.h"
#include "Game/UI/RPGGameUserInfoLayout.h"
#include "Components/Button.h"
#include "Game/RPGGameController.h"

void URPGGameUserLayout::NativeConstruct()
{
	Super::NativeConstruct();

	_UserInfoLayout = Cast<URPGGameUserInfoLayout>(GetWidgetFromName("UserInfoLayout"));
	_InventoryLayout = Cast<URPGGameInventoryLayout>(GetWidgetFromName("InventoryLayout"));
	_ExitButton = Cast<UButton>(GetWidgetFromName("ExitButton"));
	_ExitButton->OnClicked.AddDynamic(this, &URPGGameUserLayout::ExitButton);
}

URPGGameInventoryLayout* URPGGameUserLayout::GetUserInfoLayout()
{
	return _InventoryLayout;
}

void URPGGameUserLayout::ExitButton()
{
	ARPGGameController* Controller = Cast<ARPGGameController>(GetWorld()->GetFirstPlayerController());
	TArray<TSharedPtr<FRPGItemSlot>> BagData = _InventoryLayout->GetVaildBagData();
	TArray<TSharedPtr<FRPGItemSlot>> PortionSlotData = _InventoryLayout->GetVaildActionBarData();
	Controller->UpdateCharacterInfoToDB(BagData, PortionSlotData);
	UKismetSystemLibrary::QuitGame(GetWorld(), Controller, EQuitPreference::Quit, true);
}
