// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/Animation/RPGGameAttackHitCheck.h"
#include "Game/Animation/RPGGameWarriorAnim.h"

void URPGGameAttackHitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{

}

FString URPGGameAttackHitCheck::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}
