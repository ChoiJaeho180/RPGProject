// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Game/RPGGameItemStruct.h"
#include "Game/UI/RPGGameDataSlots.h"
#include "Game/UI/RPGGmaeDragBaseLayout.h"
#include "Blueprint/UserWidget.h"
#include "RPGGameBagLayout.generated.h"

class UUniformGridPanel;
class URPGGameBagslot;
class UTextBlock;
class URPGGameTitleBarLayout;
class ARPGGameDataCopy;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameBagLayout : public UUserWidget
{
	GENERATED_BODY()
	
private:
	bool _bRestInit;
	UPROPERTY()
	UUniformGridPanel* _BagGridPanel;
	UPROPERTY()
	UTextBlock* _GoldText;
	UPROPERTY()
	URPGGameTitleBarLayout* _TitleBarLayout;
	UPROPERTY()
	ARPGGameDataCopy* _CheckBagSlotData;
	UPROPERTY()
	TArray<URPGGameBagslot*> _SlotData;

	TSharedPtr<FMoney> _Money;
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
public:
	TArray<TSharedPtr<FRPGItemSlot>> GetValidSlotData();
	void InitBagSlots(const TArray<FRPGRestItem>& RestItemData);
	TSharedPtr<FRPGItemInfo> FindItem(const TSharedPtr<FRPGItemInfo>& NewItem, const TArray<TSharedPtr<FRPGItemInfo>>& NewItemsInfo);
	URPGGameBagslot* FindItem(const TSharedPtr<FRPGItemInfo>& NewItem);
	void UpdateNewSlot(const TSharedPtr<FRPGItemInfo>& NewItem);
	int FindEmptySlotIndex();
};
