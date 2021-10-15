// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Animation/Enemy/RPGGameEnemyBaseAnim.h"

void URPGGameEnemyBaseAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();

	// 유효하지 않으면 함수 종료
	if (!::IsValid(Pawn)) return;

	// 살아 있다면
	if (!_isDie)
	{
		_CurrentSpeed = Pawn->GetVelocity().Size();
	}

}