// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Game/Animation/RPGGameWarriorAnim.h"
#include "UObject/NoExportTypes.h"
#include "RPGGameComboAttackAnim.generated.h"

class UAnimMontage;

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameComboAttackAnim : public UObject
{
	GENERATED_BODY()
private:
	UPROPERTY()
	URPGGameWarriorAnim* _AnimInstance;
private:
	bool _bIsAttacking;
	bool _bIsComboInputOn;
	bool _bCanNextCombo;
	int32 _CurrentCombo;
	int32 _MaxCombo;
	TArray<float> _ComboCoefficient;
public:

	URPGGameComboAttackAnim();
	void SetAnimInstance(URPGGameWarriorAnim* NewAnim);
public:

	void InputAttack(EWarriorAnimType Type);
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	FName GetAttackMontageSectionName(int32 Section);
	void AttackStartComboState();
	void AttackEndComboState();
	void PlayAttackMontage();
	void JumpToAttackMontageSection();
public:
	UAnimMontage* AttackMontage;

public:
	FORCEINLINE int GetCurrentCombo() { return _CurrentCombo; }
	FORCEINLINE void SetbCanNextCombo(bool bNew) { _bCanNextCombo = bNew; }
	FORCEINLINE bool GetbIsComboInputOn() { return _bIsComboInputOn; }
	FORCEINLINE void SetbIsComboInputOn(bool bNew) { _bIsComboInputOn = bNew; }
	FORCEINLINE bool GetbIsAttacking() { return _bIsAttacking; }
	FORCEINLINE void SetbIsAttacking(bool bNew) { _bIsAttacking = bNew; }
	FORCEINLINE float GetCoefficient(float ComboIndex) { return _ComboCoefficient[ComboIndex]; }
};
