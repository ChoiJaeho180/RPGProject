// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Game/UI/RPGGameSlotDragDropBaseLayout.h"
#include "Blueprint/UserWidget.h"
#include "RPGGameBagslot.generated.h"

class UImage;

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameBagslot : public URPGGameSlotDragDropBaseLayout
{
	GENERATED_BODY()
private:
	UPROPERTY()
	UImage* _Icon;
	UPROPERTY()
	UImage* _Background;
	UPROPERTY()
	UButton* _Button;
	UPROPERTY()
	UTextBlock* _AmountText;
public:
	//virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
public:
	virtual void NativeConstruct() override;
	virtual UTexture2D* GetItemImage() const;
	virtual void UpdateUI() override;
	void UpdateNullItem();
	virtual void ActiveSlot(ESlateVisibility NewState);
	virtual URPGGameSlotDragDropBaseLayout* GetDragObject() override;
	void UpdateItem(TSharedPtr<FRPGItemInfo>& NewItemInfo);
	void Init(const FName& Name, const int& SlotIndex, const int& Count);
	void SetItem();
};
