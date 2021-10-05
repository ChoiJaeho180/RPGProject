// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Game/RPGGameItemStruct.h"
#include "Game/UI/RPGGameDataSlots.h"
#include "Blueprint/UserWidget.h"
#include "RPGGameSlotDragDropBaseLayout.generated.h"

class UImage;
class UButton;
class UTexture2D;
class UTextBlock;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameSlotDragDropBaseLayout : public UUserWidget
{
	GENERATED_BODY()
protected:
	IRPGGameDataSlots* _Parent;
	TSharedPtr<FRPGItemSlot> _ItemInfo;
	UPROPERTY()
	EItemIsFrom _ItemIsFrom;
	UPROPERTY()
	UImage* _Icon;
	UPROPERTY()
	UButton* _Button;
	UPROPERTY()
	UTextBlock* _AmountText;
protected:
    virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,UDragDropOperation*& OutOperation) override;
	virtual UTexture2D* GetItemImage() const;
	
public:
	void ActiveSlot(ESlateVisibility NewState);
	virtual void UpdateUI() {};
public:
	FORCEINLINE EItemIsFrom GetItemIsFrom() { return _ItemIsFrom; }
	FORCEINLINE void SetItemIsFrom(EItemIsFrom NewState) { _ItemIsFrom = NewState; }
	FORCEINLINE void SetParent(IRPGGameDataSlots* NewParent) { _Parent = NewParent; };
	FORCEINLINE IRPGGameDataSlots* GetSlotParent() { return _Parent; };
	FORCEINLINE TSharedPtr<FRPGItemSlot> GetItemSlotData() { return _ItemInfo; }
	FORCEINLINE void SetItemSlotData(const TSharedPtr<FRPGItemSlot> NewData) { _ItemInfo = NewData; }
	FORCEINLINE void SetItemSlotIndex(const int& SlotIndex) { _ItemInfo->SlotIndex = SlotIndex; }
public:
	TSubclassOf<UUserWidget> DraggedWidgetClass;

};
