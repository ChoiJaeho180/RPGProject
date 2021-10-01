// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "RPGGameTitleDragAndDrop.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameTitleDragAndDrop : public UDragDropOperation
{
	GENERATED_BODY()
private:
	UUserWidget* _ParentWidget;
	FVector2D _MouseOffset;
public:
	FORCEINLINE void SetParentWidget(UUserWidget* NewWidget) { _ParentWidget = NewWidget; }
	FORCEINLINE UUserWidget* GetParentWidget() { return _ParentWidget; }

	FORCEINLINE void SetMouseOffset(const FVector2D& NewMouseOffset) { _MouseOffset = NewMouseOffset; }
	FORCEINLINE FVector2D GetMouseOffset() { return _MouseOffset; }

};
