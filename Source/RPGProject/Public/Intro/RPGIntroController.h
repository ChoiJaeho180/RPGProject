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
	void RequestLobbyScarecrowCreating(const TArray<TSharedPtr<FJsonValue>>& Info);
public:
	ARPGIntroUIManager* GetUIManager() const;
	void SetPlayerStart(const EIntroUIWidgetState& NewState);
	virtual void SetupInputComponent() override;
	void ChangeEmotionAnim(const int& ScarecrowIndex);
public:
	TSubclassOf<ARPGIntroUIManager> _IntroUIManagerClass;
};
