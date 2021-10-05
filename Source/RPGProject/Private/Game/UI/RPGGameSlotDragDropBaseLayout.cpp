// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameSlotDragDropBaseLayout.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Game/UI/RPGGameSlotDragDropOperation.h"
#include "Common/RPGCommonGameInstance.h"
#include "Components/Image.h"
#include "Components/Button.h"

FReply URPGGameSlotDragDropBaseLayout::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    FEventReply reply;
	reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

    if (GetItemImage() == nullptr) return reply.NativeReply;

	reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, FKey("LeftMouseButton"));
	return reply.NativeReply;
}

void URPGGameSlotDragDropBaseLayout::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
    if (GetItemImage() == nullptr) return;

    URPGGameSlotDragDropOperation* ItemOperation = Cast<URPGGameSlotDragDropOperation>(UWidgetBlueprintLibrary::CreateDragDropOperation(URPGGameSlotDragDropOperation::StaticClass()));

    if (IsValid(ItemOperation) == true)
    {
        URPGCommonGameInstance* GI = Cast<URPGCommonGameInstance>(GetGameInstance());
        URPGGameSlotDragDropBaseLayout* DraggedItem = CreateWidget<URPGGameSlotDragDropBaseLayout>(GetWorld(), GI->RPGSlotClass);
        
        DraggedItem->_Icon = Cast<UImage>(DraggedItem->GetWidgetFromName("IconImage"));
        DraggedItem->_Button = Cast<UButton>(DraggedItem->GetWidgetFromName("IconButton"));
        if (DraggedItem->_Icon != nullptr)
        {
            DraggedItem->_Icon->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
            DraggedItem->_Button->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
            DraggedItem->_Icon->SetBrushFromTexture(GetItemImage());
        }
        
        ItemOperation->DefaultDragVisual = DraggedItem;
        ItemOperation->Pivot = EDragPivot::MouseDown;

        ItemOperation->InventorySlotUI = this;
        OutOperation = Cast<URPGGameSlotDragDropOperation>(ItemOperation);
    }

    UUserWidget::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
    
}

UTexture2D* URPGGameSlotDragDropBaseLayout::GetItemImage() const
{
    return nullptr;
}

void URPGGameSlotDragDropBaseLayout::ActiveSlot(ESlateVisibility NewState)
{
    _Button->SetVisibility(NewState);
    _Icon->SetVisibility(NewState);
}
