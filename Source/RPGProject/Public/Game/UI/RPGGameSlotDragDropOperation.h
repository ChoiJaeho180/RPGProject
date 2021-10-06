// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/RPGGameEnumCollection.h"
#include "Game/UI/RPGGameSlotDragDropBaseLayout.h"
#include "Blueprint/DragDropOperation.h"
#include "RPGGameSlotDragDropOperation.generated.h"

class URPGGameSlotDragDropBaseLayout;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameSlotDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
public:
	UPROPERTY()
	URPGGameSlotDragDropBaseLayout* InventorySlotUI;

public:
	void ExChangeSlot(URPGGameSlotDragDropBaseLayout* From, URPGGameSlotDragDropBaseLayout* To);
	void AddSlot(URPGGameSlotDragDropBaseLayout* From, URPGGameSlotDragDropBaseLayout* to);
	EItemIsFrom GetItemIsFrom() const { return InventorySlotUI->GetItemIsFrom(); }
};
