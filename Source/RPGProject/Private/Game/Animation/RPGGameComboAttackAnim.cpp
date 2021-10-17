// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/Animation/RPGGameComboAttackAnim.h"

URPGGameComboAttackAnim::URPGGameComboAttackAnim()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(TEXT("AnimMontage'/Game/ParagonGreystone/Characters/Heroes/Greystone/Game_Greystone_Montage.Game_Greystone_Montage'"));
	if (ATTACK_MONTAGE.Succeeded())
		AttackMontage = ATTACK_MONTAGE.Object;
	_CurrentCombo = 0;
	_MaxCombo = 3;
	_ComboCoefficient = { 1, 0.9f, 1.4f };
}

void URPGGameComboAttackAnim::InputAttack(EWarriorAnimType Type)
{
	if (_bIsAttacking)
	{
		FMath::IsWithinInclusive<int32>(_CurrentCombo, 1, _MaxCombo);
		if (_bCanNextCombo)
		{
			_bIsComboInputOn = true;
		}
	}
	else
	{
		if (_CurrentCombo != 0) return;
		AttackStartComboState();
		PlayAttackMontage();
		JumpToAttackMontageSection();
		_bIsAttacking = true;
	}
}

void URPGGameComboAttackAnim::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (_bIsAttacking == false) return;
	if (_CurrentCombo == 0) return;
	_bIsAttacking = false;
	AttackEndComboState();
}

FName URPGGameComboAttackAnim::GetAttackMontageSectionName(int32 Section)
{
	FMath::IsWithinInclusive<int32>(Section, 1, 3);
	return  FName(*FString::Printf(TEXT("Attack%d"), Section));
}

void URPGGameComboAttackAnim::AttackStartComboState()
{
	_bCanNextCombo = true;
	_bIsComboInputOn = false;
	FMath::IsWithinInclusive<int32>(_CurrentCombo, 0, _MaxCombo - 1);
	_CurrentCombo = FMath::Clamp<int32>(_CurrentCombo + 1, 1, _MaxCombo);
}

void URPGGameComboAttackAnim::AttackEndComboState()
{
	_AnimInstance->SetWarriorAnimType(EWarriorAnimType::GROUND);
	_bCanNextCombo = false;
	_bIsComboInputOn = false;
	_CurrentCombo = 0;
}

void URPGGameComboAttackAnim::PlayAttackMontage()
{
	_AnimInstance->Montage_Play(AttackMontage, 1.f);
}

void URPGGameComboAttackAnim::JumpToAttackMontageSection()
{
	if (_AnimInstance->Montage_IsPlaying(AttackMontage) == false) return;

	_AnimInstance->Montage_JumpToSection(GetAttackMontageSectionName(_CurrentCombo), AttackMontage);
}

void URPGGameComboAttackAnim::SetAnimInstance(URPGGameWarriorAnim* NewAnim)
{
	_AnimInstance = NewAnim;
}
