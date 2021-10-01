// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameTitleBarLayout.h"
#include "Game/UI/RPGGameBagslot.h"
#include "Game/UI/RPGGameTitleDragAndDrop.h"
#include "Components/Border.h"
#include "Input/Reply.h"

void URPGGameTitleBarLayout::NativeConstruct()
{
	Super::NativeConstruct();
	Visibility = ESlateVisibility::Visible;

	_TitleBorder = Cast<UBorder>(GetWidgetFromName("TitleBorder"));
}

void URPGGameTitleBarLayout::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	UE_LOG(LogTemp, Warning, TEXT("wewew"));
}

bool URPGGameTitleBarLayout::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	UE_LOG(LogTemp, Warning, TEXT("wewew"));
	return false;
}

