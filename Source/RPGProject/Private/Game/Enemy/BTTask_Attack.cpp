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
	���� �½�ũ�� ���� �ִϸ��̼��� ���� �� ���� ����ؾ� �ϴ� ���� �½�ũ�̹Ƿ�
	ExecuteTask�� ��� ���� InProgress �ϴ� ��ȯ�ϰ� ������ �������� �����ٰ� �˷������.
	-> �̸� �˷��ִ� �Լ��� FinishLatentTask��.
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
		// �׽�ũ�� �������� �˷��ִ� �Լ�
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
