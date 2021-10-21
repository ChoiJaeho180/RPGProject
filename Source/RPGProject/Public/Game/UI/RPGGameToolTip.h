// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGGameToolTip.generated.h"

class UImage;
class UTextBlock;
class UTexture2D;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameToolTip : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY()
	UImage* _ToolTipImage;
	UPROPERTY()
	UTextBlock* _Name;
	UPROPERTY()
	UTextBlock* _DescriptionText;
	UPROPERTY()
	UTextBlock*	_GoldText;
private:
	UTexture2D* _StoreImage;
	FText _StoreName;
	FText _StoreDesription;
	FText _Gold;
public:
	virtual void NativeConstruct() override;
	void SetInfo(UTexture2D* Texture, FText Name, FText Description, FText Gold);
};
