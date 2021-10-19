// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/Enemy/RPGGameEnemyBase.h"
#include "Components/WidgetComponent.h"
#include "Game/UI/Enemy/RPGGameEnemyHPWidget.h"
#include "Game/Enemy/RPGGameEnemyStatComponent.h"
#include "Game/Enemy/RPGGameBaseAIController.h"
#include "Game/Enemy/RPGGameTImer.h"
#include "Game/Animation/Enemy/RPGGameEnemyBaseAnim.h"
#include "Game/RPGGameController.h"
#include "Game/Enemy/RPGGameDamageComponent.h"

// Sets default values
ARPGGameEnemyBase::ARPGGameEnemyBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	_HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));
	_EnemyStatComponent = CreateDefaultSubobject<URPGGameEnemyStatComponent>(TEXT("EnemyStat"));
	_ActiveWidgetTimer = CreateDefaultSubobject<URPGGameTImer>(TEXT("WidgetTimer"));
	_StayDeadTimer = CreateDefaultSubobject<URPGGameTImer>(TEXT("StayDeadTimer"));
	_DamageComponent = CreateDefaultSubobject<URPGGameDamageComponent>(TEXT("DamageCompo"));
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	
	GetMesh()->SetCollisionProfileName("Enemy");
	
	_HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("WidgetBlueprint'/Game/Blueprints/GameWidgetBP/Enemy/EnemyHPBar.EnemyHPBar_C'"));
	if (UI_HUD.Succeeded())
	{
		_HPBarWidget->SetWidgetClass(UI_HUD.Class);
		
	}

	SetHiddenHPWidgetBar(true);
	
	_HPBarWidget->SetupAttachment(GetMesh());

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
	UE_LOG(LogTemp, Warning, TEXT("Begin Play"));
	auto EnemyWidget = Cast<URPGGameEnemyHPWidget>(_HPBarWidget->GetUserWidgetObject());
	if (EnemyWidget !=  nullptr ) EnemyWidget->BindCharacterStat(_EnemyStatComponent);

	_EnemyStatComponent->OnHPIsZero.AddLambda([this]() -> void
	{
		_Anim->SetDie(true);
		ARPGGameBaseAIController* AIController = Cast<ARPGGameBaseAIController>(GetController());
		AIController->StopAI();
		ARPGGameController* PlayerController = Cast<ARPGGameController>(GetWorld()->GetFirstPlayerController());
		PlayerController->AddExp(_EnemyStatComponent->GetExp());
		SetActorEnableCollision(false);
		_StayDeadTimer->SetStandardTime(3);
	});

	_ActiveWidgetTimer->delegateAchieveTime.BindLambda([this]() -> void {
		SetHiddenHPWidgetBar(true);
	});
	_StayDeadTimer->delegateAchieveTime.BindLambda([this]() -> void {
		
		delegateOnDead.ExecuteIfBound(this);
	});
}

void ARPGGameEnemyBase::Init(int HP, EEnemyType Type, int Exp, int AvegGold, TArray<int> BaseAttack)
{
	_EnemyStatComponent->Init(HP, Type, Exp, AvegGold, BaseAttack);
}

void ARPGGameEnemyBase::Response()
{
	_Anim->SetAttacking(false);
	_Anim->SetHit(false);
	_Anim->SetDie(false);
	SetHiddenHPWidgetBar(false);
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	_EnemyStatComponent->Response();
}

void ARPGGameEnemyBase::SetHiddenHPWidgetBar(bool bNew)
{
	_HPBarWidget->SetHiddenInGame(bNew);
	_ActiveWidgetTimer->SetStandardTime(3);
}

void ARPGGameEnemyBase::GetHit(int Damage)
{
	_EnemyStatComponent->SetDamage(Damage);
	_DamageComponent->AttachWidget(Damage, GetWorld()->GetFirstPlayerController(), GetActorLocation());
	_Anim->SetHit(true);
}

void ARPGGameEnemyBase::Attack(bool bNew)
{
	_Anim->SetAttacking(bNew);
}

void ARPGGameEnemyBase::SetBaseAttackType()
{
	int result = _Anim->SetBaseAttackType();
	_EnemyStatComponent->SetCurrentBaseAttackDamage(result);
}

EEnemyType ARPGGameEnemyBase::GetEnemyType()
{
	return _EnemyStatComponent->GetEnemyType();
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

