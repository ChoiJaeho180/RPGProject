// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Game/RPGGameItemStruct.h"
#include "Game/UI/RPGGameBaseLayout.h"
#include "RPGGameInventoryLayout.generated.h"

class URPGGameBagLayout;
class URPGGameEquipmentLayout;
class URPGGameActionBarLayout;
class URPGGameShopLayout;
class URPGGameQuestQuickLayout;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameInventoryLayout : public URPGGameBaseLayout
{
	GENERATED_BODY()
private:

	float _DeltaTime;
	UPROPERTY()
	URPGGameBagLayout* _BagLayout;
	UPROPERTY()
	URPGGameEquipmentLayout* _EquipmentLayout;
	UPROPERTY()
	URPGGameActionBarLayout* _ActionBar;
	UPROPERTY()
	URPGGameShopLayout* _ShopLayout;
	UPROPERTY()
	URPGGameQuestQuickLayout* _QuestQuickLayout;
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	void UpdateVisibility(const EInventoryUIType& NewInput);
	URPGGameActionBarLayout* GetActionBar();
	TArray<TSharedPtr<FRPGItemSlot>> GetVaildBagData();
	TArray<TSharedPtr<FRPGItemSlot>> GetVaildActionBarData();
public:
	void InitInventory(const TArray<FRPGRestItem>& RestItemData);
	void InitActionBar(const TArray<FRPGRestItem>& RestActionBar);
	void ActiveShop();
	void ActiveQuestQuick();
};
