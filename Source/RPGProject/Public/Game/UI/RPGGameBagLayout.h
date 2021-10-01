// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Game/UI/RPGGmaeDragBaseLayout.h"
#include "Blueprint/UserWidget.h"
#include "RPGGameBagLayout.generated.h"

class UUniformGridPanel;
class URPGGameBagslot;
class UTextBlock;
class URPGGameTitleBarLayout;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameBagLayout : public URPGGmaeDragBaseLayout
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	UUniformGridPanel* _BagGridPanel;
	UPROPERTY()
	TArray<URPGGameBagslot*> _BagSlots;
	UPROPERTY()
	UTextBlock* _GoldText;
	UPROPERTY()
	URPGGameTitleBarLayout* _TitleBarLayout;
public:
	virtual void NativeConstruct() override;
	void SetPosition(const FVector2D& NewPosition);
public:
};
