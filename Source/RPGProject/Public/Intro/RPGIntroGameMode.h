// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include "GameFramework/GameMode.h"
#include "RPGIntroGameMode.generated.h"

class ARPGIntroController;

/**
 * 
 */
UCLASS()
class RPGPROJECT_API ARPGIntroGameMode : public AGameMode
{
	GENERATED_BODY()
private:
	TMap<EIntroUIWidgetState, FString> _PlayerStartPoint;
	ARPGIntroController* _IntroController;
public:
	ARPGIntroGameMode();
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
	void SetPlayerStart(EIntroUIWidgetState NewState);
};
