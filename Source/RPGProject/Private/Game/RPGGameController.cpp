// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/RPGGameController.h"

ARPGGameController::ARPGGameController()
{
	PrimaryActorTick.bCanEverTick = true;

	bShowMouseCursor = true;
}
void ARPGGameController::BeginPlay()
{
	Super::BeginPlay();
	//
	SetInputMode(FInputModeGameOnly());
		
}