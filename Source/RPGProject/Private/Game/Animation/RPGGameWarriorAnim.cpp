// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/Animation/RPGGameWarriorAnim.h"
#include "Game/Animation/RPGGameGroundAnim.h"
#include "Game/RPGGameCharacter.h"
#include "Game/RPGGameController.h"
#include "Game/Animation/RPGGameComboAttackAnim.h"

URPGGameWarriorAnim::URPGGameWarriorAnim()
{
	_WarriorAnimType = EWarriorAnimType::GROUND;
	_WarriorGroundAnimType = EWarriorGroundAnimType::IDLE;
}

void URPGGameWarriorAnim::Init()
{
	_GroundAnim = NewObject<URPGGameGroundAnim>();
	ARPGGameController* Controller = Cast<ARPGGameController>(GetWorld()->GetFirstPlayerController());
	_GroundAnim->Init(Controller);

	_ComboAttackAnim = NewObject<URPGGameComboAttackAnim>();
	_ComboAttackAnim->SetAnimInstance(this);
	OnMontageEnded.AddDynamic(_ComboAttackAnim, &URPGGameComboAttackAnim::OnAttackMontageEnded);
//	OnMontageEnded.AddDynamic(this, &URPGGameWarriorAnim::FinishBaseAttack);
}

void URPGGameWarriorAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = Cast<ARPGGameCharacter>(TryGetPawnOwner());
	if (!::IsValid(Pawn)) return;

	if (_WarriorAnimType == EWarriorAnimType::GROUND)
	{
		_GroundAnim->Update(Pawn->GetActorLocation(), _WarriorGroundAnimType);
	}
	// 유효하지 않으면 함수 종료
	

	// 살아 있다면
	if (!_bIsDead)
	{
		
	}
}

void URPGGameWarriorAnim::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	_ComboAttackAnim->OnAttackMontageEnded(Montage, bInterrupted);
}

void URPGGameWarriorAnim::InputAttack()
{
	if (_bIsDead == true) return;
	_WarriorGroundAnimType = EWarriorGroundAnimType::IDLE;
	//움직일 때 공격 시 제자리로 MovePoint 후 공격하도록 처리
	if (_WarriorAnimType == EWarriorAnimType::GROUND)
	{
		auto Pawn = Cast<ARPGGameCharacter>(TryGetPawnOwner());
		_GroundAnim->SetMovePoint(Pawn->GetActorLocation());
		_GroundAnim->MovePoint();
	}
	
	_ComboAttackAnim->InputAttack(_WarriorAnimType);
	_WarriorAnimType = EWarriorAnimType::BASE_ATTACK;
}

void URPGGameWarriorAnim::OnClickedMove(FVector_NetQuantize MovePoint)
{
	_GroundAnim->SetMovePoint(MovePoint);

	if ((_WarriorGroundAnimType == EWarriorGroundAnimType::RUN_START ||
		_WarriorGroundAnimType == EWarriorGroundAnimType::RUN_LOOP ||
		_WarriorGroundAnimType == EWarriorGroundAnimType::RUN_END) &&
		_WarriorAnimType == EWarriorAnimType::GROUND
		)
	{
		if (_WarriorGroundAnimType == EWarriorGroundAnimType::RUN_END)
		{
			_WarriorGroundAnimType = EWarriorGroundAnimType::RUN_LOOP;
		}
		if (_WarriorGroundAnimType == EWarriorGroundAnimType::RUN_START &&
			_GroundAnim->GetbUpdateMultipleMovePoint() == false)
			return;
		_GroundAnim->MovePoint();
		return;
	}
	_GroundAnim->SetbUpdateMultipleMovePoint(false);
	_WarriorGroundAnimType = EWarriorGroundAnimType::RUN_START;
	_WarriorAnimType = EWarriorAnimType::GROUND;
}
