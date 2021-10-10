// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "RPGGameNextAttackCheck.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameNextAttackCheck : public UAnimNotify
{
	GENERATED_BODY()
		int as;
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
	FString GetNotifyName_Implementation() const;
};
