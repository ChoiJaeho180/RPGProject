// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/Enemy/BTService_Detect.h"
#include "Game/Enemy/RPGGameBaseAIController.h"
#include "Game/Enemy/RPGGameEnemyBase.h"
#include "Game/RPGGameCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "Game/Animation/Enemy/RPGGameEnemyBaseAnim.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 0.7f;
}
bool UBTService_Detect::CheckAfterDetectRadius(APawn* AI, ARPGGameCharacter* Character, float AIDetectRadius)
{
	if (Character == nullptr) return false;
	if (Character->GetAnim()->GetDead() == true) return true;

	float resultDist = Character->GetDistanceTo(AI);
	if (resultDist > AIDetectRadius * 1.2f) return true;
	return false;
}
void UBTService_Detect::UpdateHittingTarget(UBlackboardComponent* Blackboard, ARPGGameCharacter* Target)
{
	if (Blackboard->GetValueAsObject(ARPGGameBaseAIController::TargetKey) == nullptr)
	{
		Blackboard->SetValueAsObject(ARPGGameBaseAIController::TargetKey, Target);
		UE_LOG(LogTemp, Warning, TEXT("UBTService_Detect"));
	}
}
void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ARPGGameEnemyBase* ControllingPawn = Cast<ARPGGameEnemyBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ControllingPawn) return;
	

	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();
	float DetectRadius = ControllingPawn->GetDetectRadius();

	if (nullptr == World) return;
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel5,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);

	auto Target = Cast<ARPGGameCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ARPGGameBaseAIController::TargetKey));
	if (CheckAfterDetectRadius(ControllingPawn, Target, DetectRadius) == true)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(ARPGGameBaseAIController::TargetKey, nullptr);
		return;
	}

	if (bResult)
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			ARPGGameCharacter* Character = Cast<ARPGGameCharacter>(OverlapResult.GetActor());
			
			if (ControllingPawn->GetEnemyBaseAnim()->GetHit() == true)
			{
				UpdateHittingTarget(OwnerComp.GetBlackboardComponent(), Character);
				return;
			}

			if (Character && Character->GetController()->IsPlayerController())
			{
				FVector Test = (Character->GetActorLocation() - ControllingPawn->GetActorLocation()).GetSafeNormal();
				float Dot = FVector::DotProduct(ControllingPawn->GetActorForwardVector(), Test);
				if (Dot > 0)
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsObject(ARPGGameBaseAIController::TargetKey, Character);
					//DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);
					//DrawDebugPoint(World, Character->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
					//DrawDebugLine(World, ControllingPawn->GetActorLocation(), ABCharacter->GetActorLocation(), FColor::Blue, false, 0.27f);
					//DrawDebugLine(World, ControllingPawn->GetActorLocation(), ControllingPawn->GetActorLocation() + ControllingPawn->GetActorForwardVector() * 200, FColor::Blue, false, 0.27f);
				}
				return;
			}
		}
	}
}