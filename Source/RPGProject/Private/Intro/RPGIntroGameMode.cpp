// Fill out your copyright notice in the Description page of Project Settings.
#include "Intro/RPGIntroGameMode.h"
#include "Intro/RPGIntroController.h"
#include "Intro/RPGIntroCharacter.h"

ARPGIntroGameMode::ARPGIntroGameMode()
{
	PlayerControllerClass = ARPGIntroController::StaticClass();
	DefaultPawnClass = ARPGIntroCharacter::StaticClass();
}