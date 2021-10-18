// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/Skill/RPGGameAbilityR.h"
#include "Game/RPGGameCharacter.h"
#include "Game/Animation/RPGGameWarriorSkillAnim.h"
#include "Game/Animation/RPGGameGroundAnim.h"
#include "Game/RPGGameDataTableManager.h"
#include "Common/RPGCommonGameInstance.h"

void ARPGGameAbilityR::Init()
{
	_CharacterMaxSpeed = 80;
	_RestoreMaxSpeed = 600;

	URPGGameDataTableManager* DTManager = Cast<URPGCommonGameInstance>(GetWorld()->GetGameInstance())->GetDataTableManager();
	_SkillInfo = *DTManager->GetSkillNameToData("Cut the Ground");
	_CurrentCoolDown = _SkillInfo._CoolDown;
}

void ARPGGameAbilityR::ApplyProperty(ACharacter* pawn)
{

	if (pawn->GetVelocity() == FVector::ZeroVector) return;

	pawn->GetCharacterMovement()->MaxWalkSpeed = _CharacterMaxSpeed;
	Cast<ARPGGameCharacter>(pawn)->GetAnim()->GetGroundAnim()->SetMovePoint(pawn->GetActorLocation() + pawn->GetActorForwardVector() * 100);
	Cast<ARPGGameCharacter>(pawn)->GetAnim()->GetGroundAnim()->MovePoint();
}

void ARPGGameAbilityR::RestoreProperty(ACharacter* pawn)
{
	pawn->GetCharacterMovement()->MaxWalkSpeed = _RestoreMaxSpeed;
}
