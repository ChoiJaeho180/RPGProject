// Fill out your copyright notice in the Description page of Project Settings.
#include "Intro/RPGIntroCharacter.h"
#include "DrawDebugHelpers.h"
// Sets default values
ARPGIntroCharacter::ARPGIntroCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* scene_compo = CreateDefaultSubobject<USceneComponent>(TEXT("scene_compo"));
	
	RootComponent = scene_compo;
}

// Called when the game starts or when spawned
void ARPGIntroCharacter::BeginPlay()
{
	Super::BeginPlay();
	//EnableInput(GetController());
}

// Called every frame
void ARPGIntroCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARPGIntroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}



