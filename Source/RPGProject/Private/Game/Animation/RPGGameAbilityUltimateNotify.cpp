// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/Animation/RPGGameAbilityUltimateNotify.h"
#include "Game/RPGGameCharacter.h"
#include "DrawDebugHelpers.h"
#include "Game/Enemy/RPGGameEnemyBase.h"
#include "Game/RPGGameAttackJudgement.h"
#include "Game/RPGGamePlayerState.h"
#include "Game/Enemy/RPGGameEnemyBase.h"
#include "Game/Enemy/RPGGameEnemyStatComponent.h"
#include "Game/Skill/RPGGameBaseEffect.h"

void URPGGameAbilityUltimateNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ARPGGameCharacter* Character = Cast<ARPGGameCharacter>(MeshComp->GetOwner());
	if (!::IsValid(Character)) return;
	ARPGGameBaseEffect* CurrentSkill = Character->GetUseCurrentSkill();

	UE_LOG(LogTemp, Warning, TEXT("URPGGameAbilityUltimateNotify"));
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, Character);
	bool bResult = Character->GetWorld()->OverlapMultiByChannel(
		OverlapResults,
		Character->GetActorLocation() + Character->GetActorForwardVector() * CurrentSkill->GetAttackLocation(),
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel4,
		FCollisionShape::MakeSphere(CurrentSkill->GetAttackRadius()),
		CollisionQueryParam
	);
	if (bResult == false) return;
	ARPGGamePlayerState* PlayerState = Cast<ARPGGamePlayerState>(Character->GetPlayerState());
	int CharacterSTX = PlayerState->GetCharacterStat()->Stat["STX"];
	int CharacterLevel = PlayerState->GetCharacterStat()->Stat["LEVEL"];
	float SkillCoefficient = CurrentSkill->GetCoefficient();

	for (auto const& OverlapResult : OverlapResults)
	{
		ARPGGameEnemyBase* Enemy = Cast<ARPGGameEnemyBase>(OverlapResult.GetActor());
		if (!::IsValid(Enemy)) continue;
		URPGGameEnemyStatComponent* EnemyStat = Enemy->GetEnemyStatCompo();
		int EnemyLevel = Enemy->GetEnemyStatCompo()->GetLevel();
		int Damage = URPGGameAttackJudgement::GetInstance()->JudgeAblityAttack(CharacterSTX, SkillCoefficient, CharacterLevel, EnemyLevel);
		Enemy->SetHiddenHPWidgetBar(false);
		Enemy->GetHit(Damage);

	}
	DrawDebugSphere(Character->GetWorld(), Character->GetActorLocation(), 800, 16, FColor::Green, false, 20.f);
}

FString URPGGameAbilityUltimateNotify::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}
