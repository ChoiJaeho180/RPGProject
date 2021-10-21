// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/RPGGameNPC.h"
#include "Runtime/Engine/Classes/Animation/AnimInstance.h"
#include "Components/WidgetComponent.h"
#include "Game/UI/RPGGameNPCSaying.h"
#include "Game/UI/RPGGameNPCTypeWidget.h"
#include "Game/Enemy/RPGGameTImer.h"
// Sets default values
ARPGGameNPC::ARPGGameNPC()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	_SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));

	_WidgetCompo = CreateDefaultSubobject<UWidgetComponent>(TEXT("ChattingWidget"));
	_WidgetCompo->SetupAttachment(_SkeletalMesh);
	_WidgetCompo->SetRelativeRotation(FRotator(10.f, 0.f, 0.f));
	_WidgetCompo->SetWidgetSpace(EWidgetSpace::Screen);

	_SpeechTimer = CreateDefaultSubobject<URPGGameTImer>(TEXT("ActiveSpeechTimer"));

	_SkeletalMesh->SetCollisionProfileName(TEXT("NPC"));
	
	RootComponent = _SkeletalMesh;
}

// Called when the game starts or when spawned
void ARPGGameNPC::BeginPlay()
{
	Super::BeginPlay();
	_SpeechTimer->delegateAchieveTime.BindUObject(this, &ARPGGameNPC::ActiveSpeech);
}
void ARPGGameNPC::ActiveSpeech()
{
	_bActiveSpeechWidget = !_bActiveSpeechWidget;

	_WidgetCompo->SetHiddenInGame(_bActiveSpeechWidget);
	_SpeechTimer->SetStandardTime(_bActiveSpeechWidget == false ? _SpeechSetInterval : _SpeechSetInterval/2);
//	UE_LOG(LogTemp, Warning, TEXT("ActiveSpeech"));
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


void ARPGGameNPC::SetSpeech()
{
	auto NPCWidget = Cast<URPGGameNPCSaying>(_WidgetCompo->GetUserWidgetObject());
	NPCWidget->NativeConstruct();
	if (NPCWidget != nullptr) NPCWidget->SetSpeechTexts(_Speech);
}
