// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/Animation/RPGGameUltimateZoomInNotify.h"
#include "Game/RPGGameCharacter.h"

void URPGGameUltimateZoomInNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ARPGGameCharacter* Character = Cast<ARPGGameCharacter>(MeshComp->GetOwner());
	if (!::IsValid(Character)) return;
	Character->SetTargetArmLength(1100);

}

FString URPGGameUltimateZoomInNotify::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}
