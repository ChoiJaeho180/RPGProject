// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/Animation/RPGGameUltimateZoomOutNotify.h"
#include "Game/RPGGameCharacter.h"

void URPGGameUltimateZoomOutNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ARPGGameCharacter* Character = Cast<ARPGGameCharacter>(MeshComp->GetOwner());
	if (!::IsValid(Character)) return;
	Character->SetTargetArmLength(4000);

}

FString URPGGameUltimateZoomOutNotify::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}
