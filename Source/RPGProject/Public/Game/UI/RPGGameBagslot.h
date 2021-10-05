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
	
public:
	//virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

public:
	virtual void NativeConstruct() override;
	virtual UTexture2D* GetItemImage() const;
	virtual void UpdateUI() override;
	void UpdateItem(TSharedPtr<FRPGItemInfo>& NewItemInfo);
	void Init(const FName& Name, const int& SlotIndex, const int& Count);
	void SetItem();
};
