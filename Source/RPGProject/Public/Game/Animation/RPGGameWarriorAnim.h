// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RPGGameWarriorAnim.generated.h"

class URPGGameGroundAnim;
class URPGGameComboAttackAnim;
class URPGGameWarriorSkillAnim;

UENUM(BlueprintType)
enum class EWarriorAnimType : uint8
{
	GROUND UMETA(DisplayName = "GROUND"),
	BASE_ATTACK UMETA(DisplayName = "BASE_ATTACK"),
	HITTING UMETA(DisplayName = "HITTING"),
	SKILL UMETA(DisplayName = "SKILL"),
	NONE UMETA(DisplayName = "NONE"),
};

UENUM(BlueprintType)
enum class EWarriorGroundAnimType : uint8
{
	RUN_START UMETA(DisplayName = "RUN_START"),
	RUN_LOOP UMETA(DisplayName = "RUN_LOOP"),
	RUN_END UMETA(DisplayName = "RUN_END"),
	IDLE UMETA(DisplayName = "IDLE"),
	NONE UMETA(DisplayName = "NONE"),
};


/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameWarriorAnim : public UAnimInstance
{
	GENERATED_BODY()
private:
	UPROPERTY()
	URPGGameGroundAnim* _GroundAnim;
	UPROPERTY()
	URPGGameComboAttackAnim* _ComboAttackAnim;
	UPROPERTY()
	URPGGameWarriorSkillAnim* _SkillAnim;
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	EWarriorAnimType _WarriorAnimType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn1, Meta = (AllowPrivateAccess = true))
	EWarriorGroundAnimType _WarriorGroundAnimType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn1, Meta = (AllowPrivateAccess = true))
	FVector _HittingDir;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool _bIsDead;

	bool _bIsAttacking;
public:
	URPGGameWarriorAnim();
	void Init();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	void InputAttack();
	void OnClickedMove(FVector_NetQuantize MovePoint);
	bool PlaySkill(const FString& KeyInput);
public:
	FORCEINLINE EWarriorAnimType GetWarriorAnimType() { return _WarriorAnimType; }
	FORCEINLINE void SetWarriorAnimType(EWarriorAnimType NewType) { _WarriorAnimType = NewType; }
	FORCEINLINE void SetGroundAnimType(EWarriorGroundAnimType NewType) { _WarriorGroundAnimType = NewType; }
	FORCEINLINE EWarriorGroundAnimType GetGroundAnimType() { return _WarriorGroundAnimType; }
	FORCEINLINE URPGGameGroundAnim* GetGroundAnim() { return _GroundAnim; }
	FORCEINLINE URPGGameComboAttackAnim* GetComboAttackAnim() { return _ComboAttackAnim; }
	FORCEINLINE void SetHittingDir(FVector New) { _HittingDir = New; }
	FORCEINLINE void SetDead(bool New) { _bIsDead = New; }
	FORCEINLINE bool GetDead() { return _bIsDead; }
};
