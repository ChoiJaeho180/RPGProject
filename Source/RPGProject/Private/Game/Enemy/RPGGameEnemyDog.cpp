// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Enemy/RPGGameEnemyDog.h"

ARPGGameEnemyDog::ARPGGameEnemyDog()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CARDBOARD(TEXT("SkeletalMesh'/Game/QuadrapedCreatures/Barghest/Meshes/SK_BARGHEST.SK_BARGHEST'"));
	if (SK_CARDBOARD.Succeeded())
	{
		_SkeletalMeshCompo->SetSkeletalMesh(SK_CARDBOARD.Object);
	}
	_CapsuleCompo->SetRelativeLocation(FVector(0, 0, 100.f));
	_CapsuleCompo->SetRelativeScale3D(FVector(2.f,10.f, 3.5f));
}

void ARPGGameEnemyDog::Init()
{
}
