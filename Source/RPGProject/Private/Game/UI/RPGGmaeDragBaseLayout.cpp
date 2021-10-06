// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGmaeDragBaseLayout.h"
#include "Game/UI/RPGGameTitleDragAndDrop.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

FReply URPGGmaeDragBaseLayout::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply reply;
	reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	UE_LOG(LogTemp, Warning, TEXT("NativeOnMouseButtonDown"));
	reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, FKey("LeftMouseButton"));
	return reply.NativeReply;
}

void URPGGmaeDragBaseLayout::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	//FVector2D NewPosition = InGeometry.AbsoluteToLocal(FDragDropEvent)
	UE_LOG(LogTemp, Warning, TEXT("NativeOnDragDetected"));

	URPGGameTitleDragAndDrop* DragAndDrop = Cast<URPGGameTitleDragAndDrop>(UWidgetBlueprintLibrary::CreateDragDropOperation(URPGGameTitleDragAndDrop::StaticClass()));
	DragAndDrop->SetParentWidget(_ParentWidget);

	DragAndDrop->SetMouseOffset(InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition()));
	DragAndDrop->DefaultDragVisual = _ParentWidget;
	DragAndDrop->Pivot = EDragPivot::MouseDown;
	OutOperation = DragAndDrop;
	_ParentWidget->RemoveFromParent();
}
