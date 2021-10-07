// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Game/UI/RPGGameSlotDragDropBaseLayout.h"
#include "RPGGameShopSlot.generated.h"

class UImage;
class UButton;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameShopSlot : public URPGGameSlotDragDropBaseLayout
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	UImage* _Icon;
	UPROPERTY()
	UImage* _Background;
	UPROPERTY()
	UButton* _Button;
public:
	virtual void NativeConstruct() override;
	virtual void ActiveSlot(ESlateVisibility NewState) override;
	virtual void UpdateUI() override;
};
