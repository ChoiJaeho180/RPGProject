// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Game/UI/RPGGameSlotDragDropBaseLayout.h"
#include "Blueprint/UserWidget.h"
#include "RPGGameActionBarSlot.generated.h"

class UTextBlock;
class UBorder;
/**
* 
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameActionBarSlot : public URPGGameSlotDragDropBaseLayout
{
	GENERATED_BODY()
private:
	UPROPERTY()
	UTextBlock* _KeyText;
	UPROPERTY()
	UBorder* _IconBorder;
	UPROPERTY()
	UBorder* _CooldownBorder;
	UPROPERTY()
	UTextBlock* _AmountText;
public:
	virtual void NativeConstruct() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
public:
	virtual void ActiveSlot(ESlateVisibility NewState) override;
	virtual void UpdateUI() override;
	void UpdateNullItem();
	void UpdateItem(const TSharedPtr<FRPGItemInfo> KeySlotData);
	virtual URPGGameSlotDragDropBaseLayout* GetDragObject() override;
	virtual UTexture2D* GetItemImage() const;
public:
	void SetKeyText(FString InputKey);
	FString GetKeyText();
};
