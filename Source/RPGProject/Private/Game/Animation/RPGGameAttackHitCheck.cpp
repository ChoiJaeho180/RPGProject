// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/Animation/RPGGameAttackHitCheck.h"
#include "Game/Animation/RPGGameWarriorAnim.h"
#include "Game/RPGGameCharacter.h"
#include "Game/Enemy/RPGGameEnemyBase.h"
#include "Game/Enemy/RPGGameEnemyStatComponent.h"
#include "Game/Animation/RPGGameComboAttackAnim.h"
#include "Game/RPGGamePlayerState.h"
#include "Game/RPGGameAttackJudgement.h"
#include "DrawDebugHelpers.h"
#include "Game/RPGGameController.h"

void URPGGameAttackHitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ARPGGameCharacter* Character = Cast<ARPGGameCharacter>(MeshComp->GetOwner());
	URPGGameWarriorAnim* Anim = Cast<URPGGameWarriorAnim>(MeshComp->GetAnimInstance());
	if (!::IsValid(Anim)) return;
	float FinalAttackRange = Character->GetBaseAttackRange();
	float FinalAttacRadius =  Character->GetBaseAttackRadius();
	// �浹�� ���Ϳ� ���õ� ������ ���� ����ü
	FHitResult HitResult;
	//FCollisionQueryParams Params2(NAME_None, FCollisionQueryParams::GetUnknownStatId());
	FCollisionQueryParams Params(NAME_None, false, Character);
	
	bool bResult = Character->GetWorld()->SweepSingleByChannel(
		HitResult,

		Character->GetActorLocation() + Character->GetActorForwardVector()* 20,
		Character->GetActorLocation() + Character->GetActorForwardVector() * FinalAttackRange,
		FQuat::Identity,
		// Attack Ʈ���̽� ä��
		ECollisionChannel::ECC_GameTraceChannel4,
		// Ž���� ���� : 50cm ������ ��ü
		FCollisionShape::MakeSphere(FinalAttacRadius),
		// ���� ����� ������ �ڽ��� �� Ž���� �������� �ʵ��� ����
		Params);

	// ���� Ž�� ���� �ð������� ǥ�� ���ֱ�

	FVector TraceVec = Character->GetActorForwardVector() * FinalAttackRange;
	FVector Center = Character->GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = FinalAttackRange * 0.5f + FinalAttacRadius;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();

	// ���� ������ �߻� : ��� �ƴϸ� ����
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 5.0f;
	/*DrawDebugCapsule(Character->GetWorld(),
		Center,
		HalfHeight,
		FinalAttacRadius,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime);
	*/
	/*
	FHitResult�� ��� ���� Actor�� ������ �Ϲ� ������ ����ȴٸ�
	�ش� �Լ������� ������ ���� ���ŵž� �� ���Ͱ� �޸𸮿� �����ִ� ������ �߻��� �� �ִ�.
	�̷��� ������ �����ϱ� ���� FHitResult�� �����κ��� �����Ӱ� ������ ������
	�������ִ� �� ������ ������� ��� ������ �����ߴ�.

	-> �� �����ͷ� ������ ���Ϳ� �����Ϸ��� IsValid �Լ��� ����� ����Ϸ���
	   ���Ͱ� ��ȿ���� ���� �����ϰ� ����ؾ��Ѵ�.
	*/

	if (bResult)
	{
		URPGGameComboAttackAnim* ComboAnim = Anim->GetComboAttackAnim();
		ARPGGamePlayerState* PlayerState = Cast<ARPGGamePlayerState>(Character->GetPlayerState());
		int ComboIndex = ComboAnim->GetCurrentCombo();

		float ComboCoefficient = ComboAnim->GetCoefficient(ComboIndex - 1);
		int CharacterSTX = PlayerState->GetCharacterStat()->Stat["STX"];
		int CharacterLevel = PlayerState->GetCharacterStat()->Stat["LEVEL"];
		if (HitResult.Actor.IsValid())
		{
			ARPGGameEnemyBase* Enemy = Cast<ARPGGameEnemyBase>(HitResult.Actor);
			if (Enemy == nullptr) return;
			Enemy->SetHiddenHPWidgetBar(false);
			int EnemyLevel = Enemy->GetEnemyStatCompo()->GetLevel();
			int ResultDamage = URPGGameAttackJudgement::GetInstance()->JudgeBaseAttack(CharacterSTX * ComboCoefficient, CharacterLevel, EnemyLevel);
			Enemy->GetHit(ResultDamage);
			Cast<ARPGGameController>(Character->GetController())->PlayerCameraManager->PlayCameraShake(Character->MyShake);
			PlayerState->AddSpecialBar(7);
		}
		
	
	}
	
}

FString URPGGameAttackHitCheck::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}
