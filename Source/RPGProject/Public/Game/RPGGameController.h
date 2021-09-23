// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include "Common/REST/RPGCommonCharacterInfoExecutor.h"
#include "GameFramework/PlayerController.h"
#include "RPGGameController.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJECT_API ARPGGameController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ARPGGameController();
	virtual void BeginPlay() override;
	void SendActiveMap(const FString& MapName);

	void SetCharacterInfo(TSharedPtr<FCharacterInfo>& NewCharacterInfo);
};
