// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/Animation/Enemy/RPGGameEnemyAttackEndNotify.h"
#include "Game/Animation/Enemy/RPGGameEnemyBaseAnim.h"

void URPGGameEnemyAttackEndNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	URPGGameEnemyBaseAnim* Anim = Cast<URPGGameEnemyBaseAnim>(MeshComp->GetAnimInstance());
	if (!::IsValid(Anim)) return;
	Anim->SetAttacking(false);
	UE_LOG(LogTemp, Warning, TEXT("Attack End"));
}


FString URPGGameEnemyAttackEndNotify::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}
