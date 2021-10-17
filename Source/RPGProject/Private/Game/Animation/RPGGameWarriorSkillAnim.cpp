// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/Animation/RPGGameWarriorSkillAnim.h"
#include "Animation/AnimMontage.h"
#include "Game/Animation/RPGGameWarriorAnim.h"

URPGGameWarriorSkillAnim::URPGGameWarriorSkillAnim()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>ABILITY_R_MONTAGE(TEXT("AnimMontage'/Game/ParagonGreystone/Characters/Heroes/Greystone/Game_Greysteon_AbilityR_Montage.Game_Greysteon_AbilityR_Montage'"));
	if (ABILITY_R_MONTAGE.Succeeded()) _Skills.Add("Q", ABILITY_R_MONTAGE.Object);
	static ConstructorHelpers::FObjectFinder<UAnimMontage>ABILITY_ULTIMATE_MONTAGE(TEXT("AnimMontage'/Game/ParagonGreystone/Characters/Heroes/Greystone/Game_Greysteon_AbilityUltimate.Game_Greysteon_AbilityUltimate'"));
	if (ABILITY_ULTIMATE_MONTAGE.Succeeded()) _Skills.Add("W", ABILITY_ULTIMATE_MONTAGE.Object);
}

bool URPGGameWarriorSkillAnim::PlaySkillAnimation(const FString& InputKey)
{
	if (_Skills.Contains(InputKey) == false) return false;
	if (_Parent->Montage_IsPlaying(_Skills[InputKey]) == true) return false;

	_Parent->Montage_Play(_Skills[InputKey]);
	return true;
}

void URPGGameWarriorSkillAnim::SetAnimParent(URPGGameWarriorAnim* NewParent)
{
	_Parent = NewParent;
}

void URPGGameWarriorSkillAnim::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (_Parent->GetWarriorAnimType() != EWarriorAnimType::SKILL) return;
	UE_LOG(LogTemp, Warning, TEXT("22222"));
	_Parent->SetWarriorAnimType(EWarriorAnimType::GROUND);
	_Parent->SetGroundAnimType(EWarriorGroundAnimType::IDLE);
}
