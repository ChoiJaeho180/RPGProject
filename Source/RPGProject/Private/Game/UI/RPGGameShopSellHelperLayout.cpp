// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameShopSellHelperLayout.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Game/RPGGameController.h"
#include "Game/RPGGamePlayerState.h"
#include "Game/RPGGameCharacterBagComponent.h"

void URPGGameShopSellHelperLayout::NativeConstruct()
{
	Super::NativeConstruct();
	_SellButton = Cast<UButton>(GetWidgetFromName("SellButton"));
	_SellButton->OnClicked.AddDynamic(this, &URPGGameShopSellHelperLayout::ClickedSellButton);

	_UnitPriceText = Cast<UTextBlock>(GetWidgetFromName("UnitPrice"));
	_MaxCountText = Cast<UTextBlock>(GetWidgetFromName("MaxCount"));
	InputText->OnTextCommitted.AddDynamic(this, &URPGGameShopSellHelperLayout::OnInputSellCount);

}

void URPGGameShopSellHelperLayout::ClickedSellButton()
{
	int InputCount = FCString::Atoi(*InputCountText.ToString());
	int MaxCount = FCString::Atoi(*_MaxCountText->GetText().ToString());
	if (MaxCount < InputCount)
		return;
	int UnitPrice = FCString::Atoi(*_UnitPriceText->GetText().ToString());
	int AddMoney = InputCount * UnitPrice;
	
	ARPGGamePlayerState* PS = Cast<ARPGGameController>(GetWorld()->GetFirstPlayerController())->GetGamePlayerState();
	URPGGameCharacterBagComponent* Bag = PS->GetCharacterBag();
	Bag->UpdateMoney(AddMoney);
	Bag->RemoveItem(_SellName, UnitPrice);
	RemoveFromParent();
}

void URPGGameShopSellHelperLayout::OnInputSellCount(const FText& Text, ETextCommit::Type CommitMethod)
{
	InputCountText = Text;
}

void URPGGameShopSellHelperLayout::SetMaxCount(int MaxCount)
{
	_MaxCountText->SetText(FText::FromString(FString::FromInt(MaxCount)));
}

void URPGGameShopSellHelperLayout::SetUnitPrice(int UnitPrice)
{
	_UnitPriceText->SetText(FText::FromString(FString::FromInt(UnitPrice)));
}
