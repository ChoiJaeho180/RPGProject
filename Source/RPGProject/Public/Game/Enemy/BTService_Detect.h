// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "BehaviorTree/BTService.h"
#include "BTService_Detect.generated.h"

class UBlackboardComponent;
class ARPGGameCharacter;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API UBTService_Detect : public UBTService
{
	GENERATED_BODY()
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,float DeltaSeconds) override;
public:
	UBTService_Detect();
	bool CheckAfterDetectRadius(APawn* AI, ARPGGameCharacter* Character, float AIDetectRadius);
	void UpdateHittingTarget(UBlackboardComponent* Blackboard, ARPGGameCharacter* Target);
};
