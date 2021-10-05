// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGGmaeDragBaseLayout.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGmaeDragBaseLayout : public UUserWidget
{
	GENERATED_BODY()
private:
	UUserWidget* _ParentWidget;
public:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
public:
	FORCEINLINE void SetParentWidget(UUserWidget* ParentWidget) { _ParentWidget = ParentWidget; }

};
