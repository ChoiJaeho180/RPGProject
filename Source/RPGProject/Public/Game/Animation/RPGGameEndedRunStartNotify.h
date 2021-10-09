// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "RPGGameEndedRunStartNotify.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameEndedRunStartNotify : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
	FString GetNotifyName_Implementation() const;
};
