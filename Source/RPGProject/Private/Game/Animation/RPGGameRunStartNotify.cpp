// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/Animation/RPGGameRunStartNotify.h"
#include "Game/RPGGameController.h"
#include "Game/RPGGameCharacter.h"
#include "Game/Animation/RPGGameWarriorAnim.h"
#include "Game/Animation/RPGGameGroundAnim.h"

void URPGGameRunStartNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	URPGGameWarriorAnim* Anim = Cast<URPGGameWarriorAnim>(MeshComp->GetAnimInstance());
	if (!::IsValid(Anim)) return;
	if (Anim->GetWarriorAnimType() != EWarriorAnimType::GROUND) return;
	if (Anim->GetGroundAnimType() != EWarriorGroundAnimType::RUN_START) return;
	UE_LOG(LogTemp, Warning, TEXT("RUN_START!!!!!!!!"))
	URPGGameGroundAnim* GroundAnim = Anim->GetGroundAnim();
	GroundAnim->SetbUpdateMultipleMovePoint(true);
	GroundAnim->MovePoint();
}

FString URPGGameRunStartNotify::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}
