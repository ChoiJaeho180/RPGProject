// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/Animation/Enemy/RPGGameEnemyGetHitEndNotify.h"
#include "Game/Animation/Enemy/RPGGameEnemyBaseAnim.h"

void URPGGameEnemyGetHitEndNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	URPGGameEnemyBaseAnim* Anim = Cast<URPGGameEnemyBaseAnim>(MeshComp->GetAnimInstance());
	if (!::IsValid(Anim)) return;
	Anim->SetHit(false);
}

FString URPGGameEnemyGetHitEndNotify::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}
