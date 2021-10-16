// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/Animation/Enemy/RPGGameGriffonAnim.h"
#include "Animation/AnimMontage.h"

URPGGameGriffonAnim::URPGGameGriffonAnim()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>ATTACK1_MONTAGE(TEXT("AnimMontage'/Game/QuadrapedCreatures/Griffon/Meshes/Griffon_BiteAttack_Montage.Griffon_BiteAttack_Montage'"));
	if (ATTACK1_MONTAGE.Succeeded()) _AttackMontages.Add(ATTACK1_MONTAGE.Object);
	static ConstructorHelpers::FObjectFinder<UAnimMontage>ATTACK2_MONTAGE(TEXT("AnimMontage'/Game/QuadrapedCreatures/Griffon/Meshes/Griffon_DoubleAttack_Montage.Griffon_DoubleAttack_Montage'"));
	if (ATTACK2_MONTAGE.Succeeded()) _AttackMontages.Add(ATTACK2_MONTAGE.Object);
	static ConstructorHelpers::FObjectFinder<UAnimMontage>ATTACK3_MONTAGE(TEXT("AnimMontage'/Game/QuadrapedCreatures/Griffon/Meshes/Griffon_LandingAttack_Montage.Griffon_LandingAttack_Montage'"));
	if (ATTACK3_MONTAGE.Succeeded()) _AttackMontages.Add(ATTACK3_MONTAGE.Object);
		
}
int URPGGameGriffonAnim::SetBaseAttackType()
{
	int Index = FMath::RandRange(0, 2);
	UE_LOG(LogTemp, Warning, TEXT("공격 타입 : %d"), Index);
	_AttackType = (EGriffonBaseAttackType)Index;
	Montage_Play(_AttackMontages[(int)_AttackType], 1.0f);
	return Index;
}

void URPGGameGriffonAnim::SetBasetAttackNone()
{
	_AttackType = EGriffonBaseAttackType::NONE;
}

void URPGGameGriffonAnim::Init()
{
	OnMontageEnded.AddDynamic(this, &URPGGameGriffonAnim::OnAttackMontageEnded);
}

void URPGGameGriffonAnim::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	UE_LOG(LogTemp, Warning, TEXT("OnAttackMontageEnded"));
}
