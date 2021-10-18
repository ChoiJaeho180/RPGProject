// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/Skill/RPGGameAbilityUltimage.h"
#include "Game/RPGGameCharacter.h"
#include "Game/Animation/RPGGameWarriorSkillAnim.h"
#include "Game/Animation/RPGGameGroundAnim.h"
#include "Game/RPGGameDataTableManager.h"
#include "Common/RPGCommonGameInstance.h"

void ARPGGameAbilityUltimage::ApplyProperty(ACharacter* pawn)
{
	_SkillState = ESkillState::ING;
}

void ARPGGameAbilityUltimage::Init()
{
	URPGGameDataTableManager* DTManager = Cast<URPGCommonGameInstance>(GetWorld()->GetGameInstance())->GetDataTableManager();
	_SkillInfo = *DTManager->GetSkillNameToData("Hack the Earth");
	_CurrentCoolDown = _SkillInfo._CoolDown;
}
