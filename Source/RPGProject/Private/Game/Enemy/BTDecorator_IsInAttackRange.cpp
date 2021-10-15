// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/Enemy/BTDecorator_IsInAttackRange.h"
#include "Game/Enemy/RPGGameEnemyBase.h"
#include "Game/Enemy/RPGGameBaseAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Game/RPGGameCharacter.h"

UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	//auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	auto ControllingPawn = Cast<ARPGGameEnemyBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ControllingPawn)
		return false;

	auto Target = Cast<ARPGGameCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ARPGGameBaseAIController::TargetKey));
	if (nullptr == Target)
		return false;

	bResult = (Target->GetDistanceTo(ControllingPawn) <= ControllingPawn->GetAttackRange());

	return bResult;
}