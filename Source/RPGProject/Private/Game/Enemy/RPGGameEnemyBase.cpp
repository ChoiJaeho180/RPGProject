// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/Enemy/RPGGameEnemyBase.h"
#include "Components/WidgetComponent.h"
#include "Game/UI/Enemy/RPGGameEnemyHPWidget.h"
#include "Game/Enemy/RPGGameEnemyStatComponent.h"
#include "Game/Enemy/RPGGameBaseAIController.h"
#include "Game/Enemy/RPGGameTImer.h"

// Sets default values
ARPGGameEnemyBase::ARPGGameEnemyBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//_SkeletalMeshCompo = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SketalCompo"));
	//_CapsuleCompo = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCompo"));
	_HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));
	_EnemyStatComponent = CreateDefaultSubobject<URPGGameEnemyStatComponent>(TEXT("EnemyStat"));
	_ActiveWidgetTimer = CreateDefaultSubobject<URPGGameTImer>(TEXT("WidgetTimer"));

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	
	GetMesh()->SetCollisionProfileName("Enemy");

	
	_HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("WidgetBlueprint'/Game/Blueprints/GameWidgetBP/Enemy/EnemyHPBar.EnemyHPBar_C'"));
	if (UI_HUD.Succeeded())
	{
		_HPBarWidget->SetWidgetClass(UI_HUD.Class);
		_HPBarWidget->SetDrawSize(FVector2D(150.0f,200.0f));
	}
	SetHiddenHPWidgetBar(true);
	
;
	_HPBarWidget->SetupAttachment(GetMesh());
	_HPBarWidget->SetRelativeLocation(FVector(0, 0, 58.f));

	AIControllerClass = ARPGGameBaseAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ARPGGameEnemyBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
}

// Called when the game starts or when spawned
void ARPGGameEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	auto EnemyWidget = Cast<URPGGameEnemyHPWidget>(_HPBarWidget->GetUserWidgetObject());
	if (EnemyWidget !=  nullptr ) EnemyWidget->BindCharacterStat(_EnemyStatComponent);

	_ActiveWidgetTimer->delegateAchieveTime.BindLambda([this]() -> void {
		SetHiddenHPWidgetBar(true);
	});
}

void ARPGGameEnemyBase::Init(int HP, EEnemyType Type, int Exp, int AvegGold)
{
	_EnemyStatComponent->Init(HP, Type, Exp, AvegGold);
}

void ARPGGameEnemyBase::SetHiddenHPWidgetBar(bool bNew)
{
	_HPBarWidget->SetHiddenInGame(bNew);
	_ActiveWidgetTimer->SetStandardTime(3);
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

