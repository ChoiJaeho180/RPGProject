// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/Enemy/RPGGameEnemyDog.h"
#include "Game/Enemy/RPGGameEnemyStatComponent.h"
#include "Game/Animation/Enemy/RPGGameDogAnim.h"
#include "Game/RPGGameController.h"
#include "Game/Enemy/RPGGameBaseAIController.h"
#include "Components/WidgetComponent.h"

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

	GetCharacterMovement()->MaxWalkSpeed = 400.f;
}

void ARPGGameEnemyDog::BeginPlay()
{
	Super::BeginPlay();

	_HPBarWidget->SetRelativeLocation(FVector(0, 0, 100.f));
	_HPBarWidget->SetDrawSize(FVector2D(150.0f, 200.0f));

	_Anim = Cast<URPGGameDogAnim>(GetMesh()->GetAnimInstance());
	
	_DetectRadius = 500.f;
	_AttackRange = 250;

	ARPGGameBaseAIController* ABAIController = Cast<ARPGGameBaseAIController>(GetController());
	ABAIController->RunAI();
}
