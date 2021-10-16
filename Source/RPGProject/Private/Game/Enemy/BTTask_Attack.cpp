// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/Enemy/BTTask_Attack.h"
#include "Game/Enemy/RPGGameBaseAIController.h"
#include "Game/Enemy/RPGGameEnemyBase.h"
#include "Game/Animation/Enemy/RPGGameEnemyBaseAnim.h"

UBTTask_Attack::UBTTask_Attack()
{
	bNotifyTick = true;
	IsAttacking = false;
}
EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	
	auto Enemy = Cast<ARPGGameEnemyBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Enemy)
		return EBTNodeResult::Failed;
	UE_LOG(LogTemp, Warning, TEXT("Attack Start"));
	Enemy->SetBaseAttackType();
	Enemy->Attack(true);
	/*
	공격 태스크는 공격 애니메이션이 끝날 때 까지 대기해야 하는 지연 태스크이므로
	ExecuteTask의 결과 값을 InProgress 일단 반환하고 공격이 끝났을때 끝났다고 알려줘야함.
	-> 이를 알려주는 함수가 FinishLatentTask다.
	*/
	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	auto Enemy = Cast<ARPGGameEnemyBase>(OwnerComp.GetAIOwner()->GetPawn());
	auto Anim = Enemy->GetEnemyBaseAnim();
	bool Attacking = Anim->GetAttacking();
	if (!Attacking)
	{
		// 테스크가 끝났음을 알려주는 함수
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
