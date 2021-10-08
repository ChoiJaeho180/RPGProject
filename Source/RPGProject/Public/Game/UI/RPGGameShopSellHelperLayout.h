// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/RPGGameItemStruct.h"
#include "Blueprint/UserWidget.h"
#include "RPGGameShopSellHelperLayout.generated.h"

class UButton;
class UTextBlock;
class UEditableTextBox;

enum EShopTransactionType
{
	SELL,
	BUY
};
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameShopSellHelperLayout : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY()
	UButton* _SellButton;
	UPROPERTY()
	UTextBlock* _UnitPriceText;
	UPROPERTY()
	UTextBlock* _MaxCountText;
	UPROPERTY(Meta = (BindWidget))
	UEditableTextBox* InputText;
	FName _SellName;
	FText InputCountText;
	EShopTransactionType _ShopTransactionType;
	TSharedPtr<FRPGItemInfo> _ItemInfo;
public:
	virtual void NativeConstruct() override;
	UFUNCTION()
	void ClickedSellButton();
	UFUNCTION()
	void OnInputSellCount(const FText& Text, ETextCommit::Type CommitMethod);
	void SetMaxCount(int MaxCount);
	void SetUnitPrice(int UnitPrice);
	void SetItemInfo(const TSharedPtr<FRPGItemInfo>& ItemInfo);
public:
	
	FORCEINLINE void SetShopTransactionType(EShopTransactionType New) { _ShopTransactionType = New; }
	FORCEINLINE void SetSellName(FName NewItem) { _SellName = NewItem; }
};
