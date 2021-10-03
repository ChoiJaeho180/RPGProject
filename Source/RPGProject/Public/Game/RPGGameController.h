// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include "Common/REST/RPGCommonCharacterInfoExecutor.h"
#include "GameFramework/PlayerController.h"
#include "RPGGameController.generated.h"

class ARPGGameUIManager;
class ARPGGameCharacter;
class ARPGGamePlayerState;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API ARPGGameController : public APlayerController
{
	GENERATED_BODY()
private:
	ARPGGameUIManager* _GameUIManager;
	ARPGGameCharacter* _Character;
	ARPGGamePlayerState* _PlayerStat;
public:
	ARPGGameController();
	virtual void BeginPlay() override;
	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;
	virtual void SetupInputComponent() override;
public:

	void SendActiveMap(const FString& MapName);
	void SetCharacterInfo(TSharedPtr<FCharacterInfo>& NewCharacterInfo);

	void MoveForward(float NewAxisValue);
	void MoveRight(float NewAxisValue);
	void LeftMouseClick();
	void Test();
public:
	TSubclassOf<ARPGGameUIManager> RPGGameUIManagerClass;
};
