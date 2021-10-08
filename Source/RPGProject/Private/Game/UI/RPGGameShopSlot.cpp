// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameShopSlot.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Common/RPGCommonGameInstance.h"
#include "Game/UI/RPGGameShopSellHelperLayout.h"
#include "Game/RPGGamePlayerState.h"
#include "Game/RPGGameCharacterBagComponent.h"
#include "Game/RPGGameController.h"

FReply URPGGameShopSlot::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply reply = Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);
	ARPGGamePlayerState* PS = Cast<ARPGGameController>(GetWorld()->GetFirstPlayerController())->GetGamePlayerState();
	URPGGameCharacterBagComponent* Bag = PS->GetCharacterBag();
	
	URPGCommonGameInstance* GI = Cast<URPGCommonGameInstance>(GetWorld()->GetGameInstance());
	URPGGameShopSellHelperLayout* SellHelperLayout = CreateWidget<URPGGameShopSellHelperLayout>(GetWorld(), GI->RPGBuyHelperClass);
	
	SellHelperLayout->SetShopTransactionType(EShopTransactionType::BUY);
	SellHelperLayout->AddToViewport(11);
	SellHelperLayout->SetUnitPrice(_ItemInfo->Price);
	int MaxCount = Bag->GetCharacterMoney()->Money == 0 ? 0 : Bag->GetCharacterMoney()->Money / _ItemInfo->Price;
	SellHelperLayout->SetMaxCount(MaxCount);
	SellHelperLayout->SetItemInfo(_ItemInfo);
	SellHelperLayout->SetPositionInViewport(FVector2D(434, 240));
	UE_LOG(LogTemp, Warning, TEXT("URPGGameShopSlot"));
	return reply;
}

void URPGGameShopSlot::NativeConstruct()
{
	Super::NativeConstruct();
	_Button = Cast<UButton>(GetWidgetFromName("IconButton"));
	_Icon = Cast<UImage>(GetWidgetFromName("IconImage"));
	_Background = Cast<UImage>(GetWidgetFromName("Background"));
	_Button->OnClicked.AddDynamic(this, &URPGGameShopSlot::BuyItem);

	Visibility = ESlateVisibility::Visible;
}

void URPGGameShopSlot::ActiveSlot(ESlateVisibility NewState)
{
	_Button->SetVisibility(NewState);
	_Icon->SetVisibility(NewState);
}

void URPGGameShopSlot::UpdateUI()
{
	if (_ItemInfo->Image == nullptr)
		ActiveSlot(ESlateVisibility::Hidden);
	else
		ActiveSlot(ESlateVisibility::SelfHitTestInvisible);

	_Icon->SetBrushFromTexture(_ItemInfo->Image);
}

void URPGGameShopSlot::BuyItem()
{
	UE_LOG(LogTemp, Warning, TEXT("NativeOnMouseButtonDoubleClick"));
}
