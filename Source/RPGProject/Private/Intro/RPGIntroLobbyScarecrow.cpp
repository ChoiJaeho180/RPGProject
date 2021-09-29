// Fill out your copyright notice in the Description page of Project Settings.
#include "Intro/RPGIntroLobbyScarecrow.h"
#include "Common/RPGCommonGameInstance.h"
#include "Intro/RPGIntroScarecrowAnimInstance.h"
#include "Intro/RPGIntroController.h"
#include "Sound/SoundCue.h"

// Sets default values
ARPGIntroLobbyScarecrow::ARPGIntroLobbyScarecrow()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	_Collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	_Collision->SetCapsuleSize(50.f, 110.f);
	_Collision->SetRelativeLocation(FVector(0, 0, 110));
	_SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	static ConstructorHelpers::FClassFinder<URPGIntroScarecrowAnimInstance> WARRIOR_ANIM(TEXT("AnimBlueprint'/Game/ParagonGreystone/Characters/Heroes/Greystone/Intro_Greystone.Intro_Greystone_C'"));
	if (WARRIOR_ANIM.Succeeded())
	{
		IntroScarecrowClass = WARRIOR_ANIM.Class;
	}
	
	USoundCue* propellerAudioCue;
	static ConstructorHelpers::FObjectFinder<USoundCue> propellerCue(TEXT("SoundCue'/Game/ParagonGreystone/Audio/Cues/Greystone_Status_Victory.Greystone_Status_Victory'"));
	propellerAudioCue = propellerCue.Object;
	_propellerAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("PropellerAudioComp"));
	_propellerAudioComponent->bAutoActivate = false;

	_SkeletalMesh->SetEnableGravity(true);
	RootComponent = _SkeletalMesh;
	_propellerAudioComponent->AttachTo(_SkeletalMesh);
	_propellerAudioComponent->SetSound(propellerAudioCue);
}

void ARPGIntroLobbyScarecrow::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	URPGCommonGameInstance* GameInstance = Cast<URPGCommonGameInstance>(GetGameInstance());
	_SkeletalMesh->SetSkeletalMesh(GameInstance->CharacterSkeletalMeshObject);
	_SkeletalMesh->SetAnimInstanceClass(IntroScarecrowClass);
	_Collision->AttachTo(_SkeletalMesh);

	_AnimInstance = Cast<URPGIntroScarecrowAnimInstance>(_SkeletalMesh->GetAnimInstance());
	_AnimInstance->OnMontageEnded.AddDynamic(this, &ARPGIntroLobbyScarecrow::OnNextLevelEnded);
	//_AnimInstance->Montage_SetEndDelegate(_AnimInstance->EndDelegate);
}
// Called when the game starts or when spawned
void ARPGIntroLobbyScarecrow::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARPGIntroLobbyScarecrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARPGIntroLobbyScarecrow::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ARPGIntroLobbyScarecrow::UpdateChooseAnim(bool bNew)
{
	_AnimInstance->SetNextLevel(bNew);
	_AnimInstance->PlayChooseAnim();
	_propellerAudioComponent->Play();
}

void ARPGIntroLobbyScarecrow::OnNextLevelEnded(UAnimMontage* Montage, bool bInterrupted)
{
	ARPGIntroController* IntroController = Cast<ARPGIntroController>(GetWorld()->GetFirstPlayerController());
	IntroController->PreChangeLevel();
}
