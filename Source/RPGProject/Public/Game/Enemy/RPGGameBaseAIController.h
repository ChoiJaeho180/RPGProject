// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "AIController.h"
#include "RPGGameBaseAIController.generated.h"


class UBehaviorTree;
class UBlackboardData;

/**
 * 
 */
UCLASS()
class RPGPROJECT_API ARPGGameBaseAIController : public AAIController
{
	GENERATED_BODY()
protected:

public:
	ARPGGameBaseAIController();
	virtual void OnPossess(APawn* InPawn) override;
	static const FName PatrolPosKey;
	static const FName HomePosKey;
	static const FName TargetKey;
	void RunAI();
	void StopAI();
public:
	UBehaviorTree* BTAsset;
	UBlackboardData* BBAsset;
};
