// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/RPGGameNPC.h"
#include "Runtime/Engine/Classes/Animation/AnimInstance.h"
#include "Components/WidgetComponent.h"

// Sets default values
ARPGGameNPC::ARPGGameNPC()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	_SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	_WidgetCompo = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	_WidgetCompo->SetupAttachment(_SkeletalMesh);
	_WidgetCompo->SetRelativeLocation(FVector(30.0f, 0.0f, 270.0f));
	_WidgetCompo->SetRelativeRotation(FRotator(10.f, 0.f, 0.f));
	_WidgetCompo->SetWidgetSpace(EWidgetSpace::Screen);
	_SkeletalMesh->SetCollisionProfileName(TEXT("NPC"));
	
	RootComponent = _SkeletalMesh;
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

void ARPGGameNPC::SetInfo(USkeletalMesh* NewSkeletalMesh,TSubclassOf<UAnimInstance> NewAnim, FVector NewPosition, FString NewVillage, FString NewName, FString NewType, bool bQuestor, TArray<FString> Speech)
{
	_SkeletalMesh->SetSkeletalMesh(NewSkeletalMesh);
	_SkeletalMesh->SetAnimInstanceClass(NewAnim);
	SetActorLocation(NewPosition);
	SetActorScale3D(FVector(1.25f, 1.25f, 1.25f));
	_Village = NewVillage;
	_Name = NewName;
	_Type = NewType;
	_bQuestor = bQuestor;
	_Speech = Speech;
}

