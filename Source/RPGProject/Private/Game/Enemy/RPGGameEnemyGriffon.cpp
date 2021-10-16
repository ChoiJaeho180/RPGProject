// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/Enemy/RPGGameEnemyGriffon.h"
#include "Game/Animation/Enemy/RPGGameGriffonAnim.h"
#include "Game/RPGGameController.h"
#include "Game/Enemy/RPGGameBaseAIController.h"
#include "Components/WidgetComponent.h"
ARPGGameEnemyGriffon::ARPGGameEnemyGriffon()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CARDBOARD(TEXT("SkeletalMesh'/Game/QuadrapedCreatures/Griffon/Meshes/SK_Griffon.SK_Griffon'"));
	if (SK_CARDBOARD.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_CARDBOARD.Object);
	}
	
	static ConstructorHelpers::FClassFinder<URPGGameGriffonAnim> GRIFFON_ANIM(TEXT("AnimBlueprint'/Game/QuadrapedCreatures/Griffon/Meshes/Game_Griffon.Game_Griffon_C'"));
	if (GRIFFON_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(GRIFFON_ANIM.Class);
	}
	
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -70.0f), FRotator(0.0f, -90.0f, 0.0f));
	
	GetCharacterMovement()->MaxWalkSpeed = 350.f;
}

void ARPGGameEnemyGriffon::BeginPlay()
{
	Super::BeginPlay();

	_HPBarWidget->SetRelativeLocation(FVector(0, 0, 170.f));
	_HPBarWidget->SetDrawSize(FVector2D(250.0f, 200.0f));
	_Anim = Cast<URPGGameGriffonAnim>(GetMesh()->GetAnimInstance());
	((URPGGameGriffonAnim*)_Anim)->Init();
	SetActorScale3D(FVector(0.9f, 0.9f, 0.9f));

	_DetectRadius = 600.f;
	_AttackRange = 470.f;

	ARPGGameBaseAIController* ABAIController = Cast<ARPGGameBaseAIController>(GetController());
	ABAIController->RunAI();
}
