// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/RPGGameCharacter.h"

// Sets default values
ARPGGameCharacter::ARPGGameCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	//GetCharacterMovement()->bRequestedMoveUseAcceleration
}

// Called when the game starts or when spawned
void ARPGGameCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARPGGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ARPGGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ARPGGameCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ARPGGameCharacter::MoveRight);
}

void ARPGGameCharacter::MoveForward(float NewAxisValue)
{
	AddMovementInput(GetActorForwardVector(), NewAxisValue);
}

void ARPGGameCharacter::MoveRight(float NewAxisValue)
{
	AddMovementInput(GetActorRightVector(), NewAxisValue);
}


