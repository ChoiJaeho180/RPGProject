// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/Enemy/RPGGameEnemyDog.h"
#include "Game/Enemy/RPGGameEnemyStatComponent.h"
#include "Game/Animation/Enemy/RPGGameDogAnim.h"
#include "Game/RPGGameController.h"
#include "Game/Enemy/RPGGameBaseAIController.h"

ARPGGameEnemyDog::ARPGGameEnemyDog()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CARDBOARD(TEXT("SkeletalMesh'/Game/QuadrapedCreatures/Barghest/Meshes/SK_BARGHEST.SK_BARGHEST'"));
	if (SK_CARDBOARD.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_CARDBOARD.Object);
	}

	static ConstructorHelpers::FClassFinder<URPGGameDogAnim> DOG_ANIM(TEXT("AnimBlueprint'/Game/QuadrapedCreatures/Barghest/Meshes/GameDogAnim.GameDogAnim_C'"));
	if (DOG_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(DOG_ANIM.Class);
	}
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -70.0f), FRotator(0.0f, -90.0f, 0.0f));

	//_CapsuleCompo->SetRelativeLocation(FVector(0, 0, 100.f));
	//_CapsuleCompo->SetRelativeScale3D(FVector(2.f,10.f, 3.5f));
}

void ARPGGameEnemyDog::BeginPlay()
{
	Super::BeginPlay();
	_DogAnim = Cast<URPGGameDogAnim>(GetMesh()->GetAnimInstance());
	_EnemyStatComponent->OnHPIsZero.AddLambda([this]() -> void
	{
		_DogAnim->SetDie(true);
		ARPGGameController* PlayerController = Cast<ARPGGameController>(GetWorld()->GetFirstPlayerController());
		PlayerController->AddExp(_EnemyStatComponent->GetExp());
		SetActorEnableCollision(false);
	});
	ARPGGameBaseAIController* ABAIController = Cast<ARPGGameBaseAIController>(GetController());
	ABAIController->RunAI();
}
