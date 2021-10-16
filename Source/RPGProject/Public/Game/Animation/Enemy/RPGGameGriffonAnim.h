// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Animation/Enemy/RPGGameEnemyBaseAnim.h"
#include "RPGGameGriffonAnim.generated.h"

class UAnimMontage;

UENUM(BlueprintType)
enum class EGriffonBaseAttackType : uint8
{
	BITE_ATTACK UMETA(DisplayName = "BITE_ATTACK"),
	COMBO_ATTACK UMETA(DisplayName = "COMBO_ATTACK"),
	LANDING_ATTACK UMETA(DisplayName = "LANDING_ATTACK"),
	NONE UMETA (DisplayName = "NONE")
};

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameGriffonAnim : public URPGGameEnemyBaseAnim
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	EGriffonBaseAttackType _AttackType;
	UPROPERTY()
	TArray<UAnimMontage*> _AttackMontages;
public:
	URPGGameGriffonAnim();
	virtual int SetBaseAttackType() override;
	virtual void SetBasetAttackNone() override;
	void Init();
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
};
