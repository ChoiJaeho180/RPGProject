// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/UI/RPGGameTitleDragAndDrop.h"

void URPGGameTitleDragAndDrop::CorrectPosition(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent)
{//
	GetParentWidget()->AddToViewport();
	
	FVector2D NewPosition =InDragDropEvent.GetLastScreenSpacePosition();
	UE_LOG(LogTemp, Warning, TEXT("%f, %f"), NewPosition.X, NewPosition.Y);
	GetParentWidget()->SetPositionInViewport(NewPosition, false);
}
