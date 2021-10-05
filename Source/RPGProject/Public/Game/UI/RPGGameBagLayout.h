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
class RPGPROJECT_API URPGGameBagLayout : public UUserWidget, public IRPGGameDataSlots
{
	GENERATED_BODY()
	
private:
	float _DeltaTime;
	UPROPERTY()
	UUniformGridPanel* _BagGridPanel;
	UPROPERTY()
	UTextBlock* _GoldText;
	UPROPERTY()
	URPGGameTitleBarLayout* _TitleBarLayout;
	UPROPERTY()
	ARPGGameDataCopy* _CheckBagSlotData;
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
public:
	void InitBagSlots(const TArray<FRPGRestItem>& RestItemData);
};
