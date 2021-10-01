// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Blueprint/UserWidget.h"
#include "RPGGameTitleBarLayout.generated.h"

class UBorder;

DECLARE_DELEGATE_OneParam(FTitleDragAndDropDelegate,const FVector2D&);
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameTitleBarLayout : public UUserWidget
{
	GENERATED_BODY()
private:
	UBorder* _TitleBorder;
public:
	virtual void NativeConstruct() override;
public:
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
public:
	FTitleDragAndDropDelegate delegateTitleDragAndDrop;
};
