// Fill out your copyright notice in the Description page of Project Settings.
#include "Intro/RPGIntroGameMode.h"
#include "Intro/RPGIntroController.h"
#include "Intro/RPGIntroCharacter.h"
#include "Common/RPGCommonGameInstance.h"

ARPGIntroGameMode::ARPGIntroGameMode()
{
	PlayerControllerClass = ARPGIntroController::StaticClass();
	DefaultPawnClass = ARPGIntroCharacter::StaticClass();
}

void ARPGIntroGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	URPGCommonGameInstance* GameInstance = Cast<URPGCommonGameInstance>(GetGameInstance());
	GameInstance->Release();
}
