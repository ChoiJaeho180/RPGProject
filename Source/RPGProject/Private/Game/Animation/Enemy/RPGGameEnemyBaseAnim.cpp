// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Animation/Enemy/RPGGameEnemyBaseAnim.h"

void URPGGameEnemyBaseAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();

	// ��ȿ���� ������ �Լ� ����
	if (!::IsValid(Pawn)) return;

	// ��� �ִٸ�
	if (!_isDie)
	{
		_CurrentSpeed = Pawn->GetVelocity().Size();
	}

}