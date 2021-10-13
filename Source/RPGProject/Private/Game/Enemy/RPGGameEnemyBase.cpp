// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/Enemy/RPGGameEnemyBase.h"
#include "Components/WidgetComponent.h"
#include "Game/Enemy/RPGGameEnemyStatComponent.h"

// Sets default values
ARPGGameEnemyBase::ARPGGameEnemyBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_SkeletalMeshCompo = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SketalCompo"));
	_CapsuleCompo = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCompo"));
	_HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));

	_SkeletalMeshCompo->SetCollisionProfileName("Enemy");

	
	_HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("WidgetBlueprint'/Game/Blueprints/GameWidgetBP/Enemy/EnemyHPBar.EnemyHPBar_C'"));
	if (UI_HUD.Succeeded())
	{
		_HPBarWidget->SetWidgetClass(UI_HUD.Class);
		_HPBarWidget->SetDrawSize(FVector2D(150.0f,150.0f));
	}
	_HPBarWidget->SetHiddenInGame(true);

	RootComponent = _SkeletalMeshCompo;
	_CapsuleCompo->AttachTo(_SkeletalMeshCompo);
	_HPBarWidget->SetupAttachment(_CapsuleCompo);

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

