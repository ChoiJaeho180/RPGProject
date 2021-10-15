// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RPGGameEnemyBaseAnim.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameEnemyBaseAnim : public UAnimInstance
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool _isDie;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float _CurrentSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool _isGetHit;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool _isAttacking;
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
public:
	FORCEINLINE void SetDie(bool bNewStat) { _isDie = bNewStat; }
	FORCEINLINE void SetHit(bool bNewStat) { _isGetHit = bNewStat; }
	FORCEINLINE bool GetHit() { return _isGetHit; }
	FORCEINLINE void SetAttacking(bool bNewStat) { _isAttacking = bNewStat; }
	FORCEINLINE bool GetAttacking() { return _isAttacking; }
};
