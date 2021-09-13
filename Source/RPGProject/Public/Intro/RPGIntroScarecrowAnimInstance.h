// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RPGIntroScarecrowAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGIntroScarecrowAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Pawn, Meta=(AllowPrivateAccess=true))
	bool _bNextLevel;
public:
	URPGIntroScarecrowAnimInstance();

	FORCEINLINE void SetNextLevel(bool bNew) { _bNextLevel = bNew; }
};
