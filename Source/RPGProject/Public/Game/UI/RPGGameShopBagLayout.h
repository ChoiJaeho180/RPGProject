// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/UI/RPGGameBaseLayout.h"
#include "RPGGameShopBagLayout.generated.h"

class UButton;
class URPGGameShopSlot;

DECLARE_DELEGATE(FCloseLayoutDelegate)
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameShopBagLayout : public URPGGameBaseLayout
{
	GENERATED_BODY()
private:
	UPROPERTY()
	UButton* _CloseButton;
	UPROPERTY()
	TArray<URPGGameShopSlot*> _ShopSlotData;
public:
	virtual void NativeConstruct() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	UFUNCTION()
	void CloseButton();
public:
	FCloseLayoutDelegate delegateCloseLayout;
	
};
//
