// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "UObject/NoExportTypes.h"
#include "RPGGameWarriorSkillAnim.generated.h"

class UAnimMontage;
class URPGGameWarriorAnim;
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameWarriorSkillAnim : public UObject
{
	GENERATED_BODY()
private:
	TMap<FString, UAnimMontage*> _Skills;
	URPGGameWarriorAnim* _Parent;
public:
	URPGGameWarriorSkillAnim();
	bool PlaySkillAnimation(const FString& InputKey);
	void SetAnimParent(URPGGameWarriorAnim* NewParent);
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
};
