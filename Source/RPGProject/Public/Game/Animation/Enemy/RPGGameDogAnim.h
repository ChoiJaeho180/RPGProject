// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RPGGameDogAnim.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameDogAnim : public UAnimInstance
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool _isDie;
public:
	FORCEINLINE void SetDie(bool bNewStat) { _isDie = bNewStat; }
};
