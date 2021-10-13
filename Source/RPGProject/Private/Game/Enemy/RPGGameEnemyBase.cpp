// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Enemy/RPGGameEnemyBase.h"

// Sets default values
ARPGGameEnemyBase::ARPGGameEnemyBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_SkeletalMeshCompo = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SketalCompo"));
	_CapsuleCompo = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCompo"));

	RootComponent = _SkeletalMeshCompo;
	_SkeletalMeshCompo->SetCollisionProfileName("Enemy");
	_SkeletalMeshCompo->SetCollisionProfileName("Enemy");
	_CapsuleCompo->AttachTo(_SkeletalMeshCompo);
	_CapsuleCompo->SetCollisionProfileName("Enemy");
}

// Called when the game starts or when spawned
void ARPGGameEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARPGGameEnemyBase::Init()
{
}

// Called every frame
void ARPGGameEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARPGGameEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

