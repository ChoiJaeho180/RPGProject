// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include "Common/REST/RPGCommonCharacterInfoExecutor.h"
#include "GameFramework/PlayerController.h"
#include "RPGGameController.generated.h"

class ARPGGameUIManager;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API ARPGGameController : public APlayerController
{
	GENERATED_BODY()
private:
	ARPGGameUIManager* _GameUIManager;
public:
	ARPGGameController();
	virtual void BeginPlay() override;
	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override; 
public:

	void SendActiveMap(const FString& MapName);
	void SetCharacterInfo(TSharedPtr<FCharacterInfo>& NewCharacterInfo);
public:
	TSubclassOf<ARPGGameUIManager> RPGGameUIManagerClass;
};
