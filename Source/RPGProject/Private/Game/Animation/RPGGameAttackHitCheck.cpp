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
	// 충돌된 액터에 관련된 정보를 가질 구조체
	FHitResult HitResult;
	//FCollisionQueryParams Params2(NAME_None, FCollisionQueryParams::GetUnknownStatId());
	FCollisionQueryParams Params(NAME_None, false, Character);
	
	bool bResult = Character->GetWorld()->SweepSingleByChannel(
		HitResult,
		// 도형의 탐색 영역
		Character->GetActorLocation(),
		Character->GetActorLocation() + Character->GetActorForwardVector() * FinalAttackRange,
		FQuat::Identity,
		// Attack 트레이스 채널
		ECollisionChannel::ECC_GameTraceChannel4,
		// 탐색할 도형 : 50cm 반지름 구체
		FCollisionShape::MakeSphere(FinalAttacRadius),
		// 공격 명령을 내리는 자신은 이 탐색에 감지되지 않도록 설정
		Params);

	// 공격 탐지 범위 시각적으로 표현 해주기

	FVector TraceVec = Character->GetActorForwardVector() * FinalAttackRange;
	FVector Center = Character->GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = FinalAttackRange * 0.5f + FinalAttacRadius;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();

	// 공격 판정이 발생 : 녹색 아니면 빨강
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 5.0f;
	DrawDebugCapsule(Character->GetWorld(),
		Center,
		HalfHeight,
		FinalAttacRadius,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime);
	/*
	FHitResult의 멤버 변수 Actor의 선언이 일반 참조로 선언된다면
	해당 함수에서의 참조로 인해 제거돼야 할 액터가 메모리에 남아있는 문제가 발생할 수 있다.
	이러한 문제를 방지하기 위해 FHitResult는 참조로부터 자유롭게 포인터 정보를
	전달해주는 약 포인터 방식으로 멤버 변수를 선언했다.

	-> 약 포인터로 지정된 액터에 접근하려면 IsValid 함수를 사용해 사용하려는
	   액터가 유효한지 먼저 점검하고 사용해야한다.
	*/

	if (bResult)
	{
		URPGGameComboAttackAnim* ComboAnim = Anim->GetComboAttackAnim();
		ARPGGamePlayerState* PlayerState = Cast<ARPGGamePlayerState>(Character->GetPlayerState());
		int ComboIndex = ComboAnim->GetCurrentCombo();
		UE_LOG(LogTemp, Warning, TEXT("%d"), ComboIndex);
		float ComboCoefficient = ComboAnim->GetCoefficient(ComboIndex - 1);
		int CharacterSTX = PlayerState->GetCharacterStat()->Stat["STX"];
		int CharacterLevel = PlayerState->GetCharacterStat()->Stat["LEVEL"];
		if (HitResult.Actor.IsValid())
		{
			ARPGGameEnemyBase* Enemy = Cast<ARPGGameEnemyBase>(HitResult.Actor);
			if (Enemy == nullptr) return;
			Enemy->SetHiddenHPWidgetBar(false);
			URPGGameEnemyStatComponent* EnemyStat = Enemy->GetEnemyStatCompo();
			int EnemyLevel = Enemy->GetEnemyStatCompo()->GetLevel();
			int ResultDamage = URPGGameAttackJudgement::GetInstance()->JudgeBaseAttack(CharacterSTX * ComboCoefficient, CharacterLevel, EnemyLevel);
			EnemyStat->SetDamage(ResultDamage);
			Enemy->GetHit(ResultDamage);
			Cast<ARPGGameController>(Character->GetController())->PlayerCameraManager->PlayCameraShake(Character->MyShake);
			//GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(Character->MyShake);
		}
		
	
	}
	
}

FString URPGGameAttackHitCheck::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}
