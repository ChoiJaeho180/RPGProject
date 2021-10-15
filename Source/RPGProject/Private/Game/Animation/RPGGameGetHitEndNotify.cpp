// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/Animation/RPGGameGetHitEndNotify.h"
#include "Game/Animation/RPGGameWarriorAnim.h"

void URPGGameGetHitEndNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	URPGGameWarriorAnim* Anim = Cast<URPGGameWarriorAnim>(MeshComp->GetAnimInstance());
	if (!::IsValid(Anim)) return;
	Anim->SetWarriorAnimType(EWarriorAnimType::GROUND);
	Anim->SetGroundAnimType(EWarriorGroundAnimType::IDLE);
}

FString URPGGameGetHitEndNotify::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}
