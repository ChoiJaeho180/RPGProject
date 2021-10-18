// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include "UObject/NoExportTypes.h"
#include "RPGGameAttackJudgement.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameAttackJudgement : public UObject
{
	GENERATED_BODY()
private:
	static URPGGameAttackJudgement* Instance;
public:
	static URPGGameAttackJudgement* GetInstance()
	{
		if (Instance == nullptr)
		{
			Instance = NewObject<URPGGameAttackJudgement>();
		}
		return Instance;
	}
public:
	int JudgeBaseAttack(int AttackDamage, int AttackerLevel, int EnemyLevel);
	int JudgeAblityAttack(int AttackDamage, float Coefficient, int AttackerLevel, int EnemyLevel);
};
