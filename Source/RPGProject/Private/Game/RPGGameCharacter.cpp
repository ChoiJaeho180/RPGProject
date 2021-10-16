// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/RPGGameCharacter.h"
#include "Game/RPGGameController.h"

// Sets default values
ARPGGameCharacter::ARPGGameCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_BaseAttackRadius = 80.f;
	_BaseAttackRange = 300.f;
}

// Called when the game starts or when spawned
void ARPGGameCharacter::BeginPlay()
{
	Super::BeginPlay();
	_WarriorAnim = Cast<URPGGameWarriorAnim>(GetMesh()->GetAnimInstance());
	_WarriorAnim->Init();
}

void ARPGGameCharacter::InputAttack()
{
	_WarriorAnim->InputAttack();
}

void ARPGGameCharacter::OnClikedMove(FVector_NetQuantize MovePoint)
{
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	_WarriorAnim->OnClickedMove(MovePoint);
}



// Called every frame
void ARPGGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (_WarriorAnim->GetWarriorAnimType() != EWarriorAnimType::BASE_ATTACK )
		return;
	
	FRotator SmoothRotator = FMath::RInterpTo(GetActorRotation(), _TargetRotator, DeltaTime, 10);
	SetActorRotation(FRotator(GetActorRotation().Pitch, SmoothRotator.Yaw, GetActorRotation().Roll));
	
}

void ARPGGameCharacter::GetHitting(FVector HitDir)
{
	_WarriorAnim->SetWarriorAnimType(EWarriorAnimType::HITTING);
	_WarriorAnim->SetHittingDir(HitDir);
}

void ARPGGameCharacter::Dead()
{
	_WarriorAnim->SetDead(true);
	GetMesh()->SetCollisionProfileName("NoCollision");
}

void ARPGGameCharacter::Resurrection()
{
	_WarriorAnim->SetDead(false);
	GetMesh()->SetCollisionProfileName("Character");
}

EWarriorAnimType ARPGGameCharacter::GetAnimState()
{
	return _WarriorAnim->GetWarriorAnimType();
}

// Called to bind functionality to input
void ARPGGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//PlayerInputComponent->BindAction(TEXT("LeftMouseClick"), EInputEvent::IE_Released, this, &ARPGGameCharacter::LeftMouseClick);
}

