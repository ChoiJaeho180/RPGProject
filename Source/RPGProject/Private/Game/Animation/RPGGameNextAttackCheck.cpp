// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/Animation/RPGGameNextAttackCheck.h"
#include "Game/Animation/RPGGameWarriorAnim.h"
#include "Game/Animation/RPGGameComboAttackAnim.h"

void URPGGameNextAttackCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	URPGGameWarriorAnim* Anim = Cast<URPGGameWarriorAnim>(MeshComp->GetAnimInstance());
	if (!::IsValid(Anim)) return;
	URPGGameComboAttackAnim* GameComboAttack = Anim->GetComboAttackAnim();
	GameComboAttack->SetbCanNextCombo(false);
	
	if (GameComboAttack->GetbIsComboInputOn() == false) return;

	GameComboAttack->AttackStartComboState();
	GameComboAttack->JumpToAttackMontageSection();

}

FString URPGGameNextAttackCheck::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}
