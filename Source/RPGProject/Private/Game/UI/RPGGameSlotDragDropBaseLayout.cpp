// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameSlotDragDropBaseLayout.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Game/UI/RPGGameSlotDragDropOperation.h"
#include "Common/RPGCommonGameInstance.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Game/UI/RPGGameToolTip.h"

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
        
        URPGGameSlotDragDropBaseLayout* DraggedItem =  GetDragObject();
        
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

void URPGGameSlotDragDropBaseLayout::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    UE_LOG(LogTemp, Warning, TEXT("NativeOnMouseEnter"));
    if (_ToolTip == nullptr) _ToolTip = CreateWidget<URPGGameToolTip>(this, Cast<URPGCommonGameInstance>(GetGameInstance())->ItemToolTipClass);
    if (GetItemImage() != nullptr)
    {
        if (_ToolTip != nullptr)
        {
            _ToolTip->SetInfo(_ItemInfo->Image, FText::FromString(_ItemInfo->Name.ToString()), _ItemInfo->Description, FText::FromString(FString::FromInt(_ItemInfo->Price)));
            SetToolTip(_ToolTip);
        }
        
        //ToolTipWidget->
      //ToolTipWidget->SetRenderScale(FVector2D(0.5f, 1));
    }
}

void URPGGameSlotDragDropBaseLayout::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
    SetToolTip(nullptr);
}

