// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/RPGGameCharacter.h"
#include "Game/RPGGameController.h"
#include "Game/Animation/RPGGameWarriorAnim.h"

// Sets default values
ARPGGameCharacter::ARPGGameCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARPGGameCharacter::BeginPlay()
{
	Super::BeginPlay();
	_WarriorAnim = Cast<URPGGameWarriorAnim>(GetMesh()->GetAnimInstance());
	_WarriorAnim->Init();
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
}

// Called to bind functionality to input
void ARPGGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//PlayerInputComponent->BindAction(TEXT("LeftMouseClick"), EInputEvent::IE_Released, this, &ARPGGameCharacter::LeftMouseClick);
}

