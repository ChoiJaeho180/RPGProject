// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/Animation/RPGGameWarriorAnim.h"
#include "Game/Animation/RPGGameGroundAnim.h"
#include "Game/RPGGameCharacter.h"
#include "Game/RPGGameController.h"

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
		_CurrentPawnSpeed = Pawn->GetVelocity().Size();
	}
}

void URPGGameWarriorAnim::OnClickedMove(FVector_NetQuantize MovePoint)
{
	_GroundAnim->SetMovePoint(MovePoint);

	if (_WarriorGroundAnimType == EWarriorGroundAnimType::RUN_START ||
		_WarriorGroundAnimType == EWarriorGroundAnimType::RUN_LOOP ||
		_WarriorGroundAnimType == EWarriorGroundAnimType::RUN_END)
	{
		_WarriorGroundAnimType = EWarriorGroundAnimType::RUN_LOOP;
		_GroundAnim->MovePoint();
		return;
	}
	_WarriorGroundAnimType = EWarriorGroundAnimType::RUN_START;
	
}
