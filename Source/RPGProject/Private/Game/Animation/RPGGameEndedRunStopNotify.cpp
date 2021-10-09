// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/Animation/RPGGameEndedRunStopNotify.h"
#include "Game/Animation/RPGGameWarriorAnim.h"

void URPGGameEndedRunStopNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	URPGGameWarriorAnim* Anim = Cast<URPGGameWarriorAnim>(MeshComp->GetAnimInstance());
	if (!::IsValid(Anim)) return;
	if (Anim->GetWarriorAnimType() != EWarriorAnimType::GROUND) return;
	if (Anim->GetGroundAnimType() != EWarriorGroundAnimType::RUN_END) return;
	UE_LOG(LogTemp, Warning, TEXT("IDLE!!!!!!!!!!!"));
	Anim->SetGroundAnimType(EWarriorGroundAnimType::IDLE);
}

FString URPGGameEndedRunStopNotify::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}
