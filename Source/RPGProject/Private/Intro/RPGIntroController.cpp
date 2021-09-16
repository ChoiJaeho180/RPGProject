// Fill out your copyright notice in the Description page of Project Settings.
#include "Intro/RPGIntroController.h"
#include "Intro/RPGIntroCharacter.h"
#include "Intro/UI/RPGIntroUIManager.h"
#include "Intro/RPGIntroGameMode.h"

ARPGIntroController::ARPGIntroController()
{
	PrimaryActorTick.bCanEverTick = true;

	_IntroUIManagerClass = ARPGIntroUIManager::StaticClass();

	bShowMouseCursor = true;
}

void ARPGIntroController::BeginPlay()
{
	Super::BeginPlay();
	
	SetInputMode(FInputModeGameOnly());

	_IntroUIManager = GetWorld()->SpawnActor<ARPGIntroUIManager>(_IntroUIManagerClass);
	_IntroUIManager->Initialize(this);
}

void ARPGIntroController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	
}

void ARPGIntroController::RequestLobbyScarecrowCreating(const TArray<TSharedPtr<FJsonValue>>& Info)
{
	ARPGIntroGameMode* GM = Cast<ARPGIntroGameMode>(GetWorld()->GetAuthGameMode());
	GM->CreateLobbyScarecrow(Info);
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

void ARPGIntroController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void ARPGIntroController::ChangeEmotionAnim(const int& ScarecrowIndex)
{
	ARPGIntroGameMode* GM = Cast<ARPGIntroGameMode>(GetWorld()->GetAuthGameMode());
	GM->UpdateChooseAnim(ScarecrowIndex);
	//GM->SetPlayerStart(NewState);
}

void ARPGIntroController::ChangeLevel()
{
	ARPGIntroGameMode* GM = Cast<ARPGIntroGameMode>(GetWorld()->GetAuthGameMode());
	GM->ChangeLevel();
}

void ARPGIntroController::PreChangeLevel()
{
	_IntroUIManager->PreChangeLevel();
}
