// Fill out your copyright notice in the Description page of Project Settings.
#include "Intro/RPGIntroGameMode.h"
#include "Intro/RPGIntroController.h"
#include "Intro/RPGIntroCharacter.h"
#include "Common/RPGCommonGameInstance.h"
#include "GameFramework/PlayerStart.h"

ARPGIntroGameMode::ARPGIntroGameMode()
{
	PlayerControllerClass = ARPGIntroController::StaticClass();
	DefaultPawnClass = ARPGIntroCharacter::StaticClass();

	_PlayerStartPoint.Add(EIntroUIWidgetState::MAIN, FString("Main_PlayerStart"));
	_PlayerStartPoint.Add(EIntroUIWidgetState::LOBBY, FString("Lobby_PlayerStart"));

}

void ARPGIntroGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	_IntroController = Cast<ARPGIntroController>(NewPlayer);
}

void ARPGIntroGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	URPGCommonGameInstance* GameInstance = Cast<URPGCommonGameInstance>(GetGameInstance());
	GameInstance->Release();
}

void ARPGIntroGameMode::SetPlayerStart(EIntroUIWidgetState NewState)
{
	if (_PlayerStartPoint.Contains(NewState) == false)
		return;
	AActor* PlayerStart = FindPlayerStart(_IntroController, _PlayerStartPoint[NewState]);
	_IntroController->GetPawn()->SetActorRelativeTransform(PlayerStart->GetActorTransform());

}
