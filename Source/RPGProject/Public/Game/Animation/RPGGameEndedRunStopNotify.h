// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "RPGGameEndedRunStopNotify.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameEndedRunStopNotify : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
	FString GetNotifyName_Implementation() const;
};
