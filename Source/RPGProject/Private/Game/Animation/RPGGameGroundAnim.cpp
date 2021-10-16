// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/Animation/RPGGameGroundAnim.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Game/RPGGameController.h"
#include "Game/RPGGameCharacter.h"

void URPGGameGroundAnim::Update(FVector PawnLocation, EWarriorGroundAnimType& GroundState)
{
	if (GroundState == EWarriorGroundAnimType::RUN_END ||
		GroundState == EWarriorGroundAnimType::IDLE)
		return;
	float Dist = FVector::Dist(PawnLocation, _MovePoint);

	if (Dist > PAWN_TO_POINT_DIST) return;
	
	GroundState = EWarriorGroundAnimType::RUN_END;
	Cast<ARPGGameCharacter>(_Controller->GetPawn())->GetCharacterMovement()->MaxWalkSpeed = 150;
}

void URPGGameGroundAnim::MovePoint()
{
	if (!::IsValid(_Controller)) return;
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(_Controller, _MovePoint);
}

void URPGGameGroundAnim::Init(ARPGGameController* NewController)
{
	_Controller = NewController;
}

