// Fill out your copyright notice in the Description page of Project Settings.
#include "Intro/RPGIntroController.h"
#include "Intro/RPGIntroCharacter.h"
#include "Intro/UI/RPGIntroUIManager.h"
#include "Intro/RPGIntroGameMode.h"

ARPGIntroController::ARPGIntroController()
{
	PrimaryActorTick.bCanEverTick = false;

	_IntroUIManagerClass = ARPGIntroUIManager::StaticClass();

	bShowMouseCursor = true;
}

void ARPGIntroController::BeginPlay()
{
	Super::BeginPlay();
	
	SetInputMode(FInputModeGameAndUI());

	_IntroUIManager = GetWorld()->SpawnActor<ARPGIntroUIManager>(_IntroUIManagerClass);
	_IntroUIManager->Initialize(this);
}

void ARPGIntroController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	
}

ARPGIntroUIManager* ARPGIntroController::GetUIManager() const
{
	return _IntroUIManager;
}

void ARPGIntroController::SetPlayerStart(const EIntroUIWidgetState& NewState)
{
	ARPGIntroGameMode* GM = Cast<ARPGIntroGameMode>(GetWorld()->GetAuthGameMode());
	GM->SetPlayerStart(NewState);
}
