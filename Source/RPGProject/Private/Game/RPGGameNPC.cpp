// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/RPGGameNPC.h"

// Sets default values
ARPGGameNPC::ARPGGameNPC()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	_SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	/*
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CARDBOARD(TEXT("SkeletalMesh'/Game/ParagonYin/Characters/Heroes/Yin/Meshes/Yin.Yin'"));
	if (SK_CARDBOARD.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_CARDBOARD.Object);
	}
	*/
	RootComponent = _SkeletalMesh;
	/*
	
	static ConstructorHelpers::FClassFinder<URPGGameWarriorAnim> WARRIOR_ANIM(TEXT("AnimBlueprint'/Game/ParagonGreystone/Characters/Heroes/Greystone/Game_Greystone.Game_Greystone_C'"));
	if (WARRIOR_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(WARRIOR_ANIM.Class);
	}
	*/
}

// Called when the game starts or when spawned
void ARPGGameNPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARPGGameNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARPGGameNPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

