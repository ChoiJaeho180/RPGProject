// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/Animation/RPGGameEndedRunStartNotify.h"
#include "Game/RPGGameCharacter.h"
#include "Game/Animation/RPGGameWarriorAnim.h"

void URPGGameEndedRunStartNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	URPGGameWarriorAnim* Anim = Cast<URPGGameWarriorAnim>(MeshComp->GetAnimInstance());
	if (!::IsValid(Anim)) return;
	if (Anim->GetWarriorAnimType() != EWarriorAnimType::GROUND) return;
	if (Anim->GetGroundAnimType() != EWarriorGroundAnimType::RUN_START) return;
	//UE_LOG(LogTemp, Warning, TEXT("RUN_LOOP!!!!!!!!!!!"));
	Anim->SetGroundAnimType(EWarriorGroundAnimType::RUN_LOOP);
}


FString URPGGameEndedRunStartNotify::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}
