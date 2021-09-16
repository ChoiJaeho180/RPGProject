// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include "GameFramework/GameMode.h"
#include "RPGGameGameMode.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJECT_API ARPGGameGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	ARPGGameGameMode();

	void PostLogin(APlayerController* NewPlayer);
	void Logout(AController* Exiting);
};
