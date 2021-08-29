// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "..\RPGProject.h"
#include "GameFramework/PlayerController.h"
#include "RPGIntroController.generated.h"

class ARPGIntroUIManager;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API ARPGIntroController : public APlayerController
{
	GENERATED_BODY()
private:
	ARPGIntroUIManager* _IntroUIManager;
public:
	ARPGIntroController();
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* aPawn) override;
public:
	TSubclassOf<ARPGIntroUIManager> _IntroUIManagerClass;
};
