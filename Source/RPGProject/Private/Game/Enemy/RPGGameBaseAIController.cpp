// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/Enemy/RPGGameBaseAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName ARPGGameBaseAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName ARPGGameBaseAIController::HomePosKey(TEXT("HomePos"));
const FName ARPGGameBaseAIController::TargetKey(TEXT("Target"));

ARPGGameBaseAIController::ARPGGameBaseAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("BlackboardData'/Game/AI/RPGGameDog_BB.RPGGameDog_BB'"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("BehaviorTree'/Game/AI/RPGGameDog_BT.RPGGameDog_BT'"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
}

void ARPGGameBaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(BBAsset, Blackboard))
	{
		///UE_LOG(LogTemp, Warning, TEXT("RunAI"));
		Blackboard->SetValueAsVector(HomePosKey, GetPawn()->GetActorLocation());
		if (!RunBehaviorTree(BTAsset))
			UE_LOG(LogTemp, Warning, TEXT("AIController couldn't run behavior tree !"));
	}
}

void ARPGGameBaseAIController::RunAI()
{
	if (UseBlackboard(BBAsset, Blackboard))
	{
		//UE_LOG(LogTemp, Warning, TEXT("RunAI"));
		Blackboard->SetValueAsVector(HomePosKey, GetPawn()->GetActorLocation());
		if (!RunBehaviorTree(BTAsset))
			UE_LOG(LogTemp,Warning, TEXT("AIController couldn't run behavior tree !"));
	}
}

void ARPGGameBaseAIController::StopAI()
{
	auto BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (nullptr != BehaviorTreeComponent)
		BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
}
