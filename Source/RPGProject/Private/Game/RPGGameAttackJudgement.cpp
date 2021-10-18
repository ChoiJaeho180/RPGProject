// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/RPGGameAttackJudgement.h"

URPGGameAttackJudgement* URPGGameAttackJudgement::Instance = nullptr;

#define DEFEASANCE_DAMAGE_LEVEL_DIFF 3
#define BASE_ATTACK_RAND_MIN -10
#define BASE_ATTACK_RAND_MAX 10
#define ANTIPATHY_RATIO 15

int URPGGameAttackJudgement::JudgeBaseAttack(int AttackDamage, int AttackerLevel, int EnemyLevel)
{
	bool bMoreLevel = AttackerLevel >= EnemyLevel;
	int LevelDiff = FMath::Abs(AttackerLevel - EnemyLevel);
	if (LevelDiff >= DEFEASANCE_DAMAGE_LEVEL_DIFF && bMoreLevel == false) return 1;
	
	int Damage = FMath::Clamp(AttackDamage + FMath::RandRange(BASE_ATTACK_RAND_MIN, BASE_ATTACK_RAND_MAX), 1, 10000000);
	if (LevelDiff == 0) return Damage;

	float CorrectionDamage = 0; 
	if (bMoreLevel == true)
	{
		CorrectionDamage = (1 + (float)(LevelDiff * ANTIPATHY_RATIO) / 100) * Damage;
	}
	else
	{
		CorrectionDamage = (1 - (float)(LevelDiff * ANTIPATHY_RATIO) / 100) * Damage;
	}

	return CorrectionDamage;
}

int URPGGameAttackJudgement::JudgeAblityAttack(int AttackDamage, float Coefficient, int AttackerLevel, int EnemyLevel)
{
	return JudgeBaseAttack(AttackDamage * Coefficient, AttackerLevel, EnemyLevel);
}
