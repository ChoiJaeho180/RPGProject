// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Game/UI/RPGGameBaseLayout.h"
#include "RPGGameInventoryLayout.generated.h"

class URPGGameBagLayout;
class URPGGameEquipmentLayout;

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameInventoryLayout : public URPGGameBaseLayout
{
	GENERATED_BODY()
private:
	UPROPERTY()
	URPGGameBagLayout* _BagLayout;
	UPROPERTY()
	URPGGameEquipmentLayout* _EquipmentLayout;
public:
	virtual void NativeConstruct() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};
