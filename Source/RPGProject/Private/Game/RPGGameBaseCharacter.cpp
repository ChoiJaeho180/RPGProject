// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/RPGGameBaseCharacter.h"
#include "Game/Animation/RPGGameWarriorAnim.h"
#include "Components/DecalComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"

// Sets default values
ARPGGameBaseCharacter::ARPGGameBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	_SpringArm->SetupAttachment(GetCapsuleComponent());
	_Camera->SetupAttachment(_SpringArm);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	_SpringArm->TargetArmLength = 1100.0f;
	_SpringArm->RelativeRotation = FRotator(-45.0f, 0.0f, 0.0f);
	_SpringArm->bUsePawnControlRotation = false;
	_SpringArm->bInheritPitch = false;
	_SpringArm->bInheritRoll = false;
	_SpringArm->bInheritYaw = false;
	_SpringArm->bDoCollisionTest = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	
	//GetCharacterMovement()->bUseControllerDesiredRotation = true;

	_CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	_CursorToWorld->SetupAttachment(RootComponent);
	

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CARDBOARD(TEXT("SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Meshes/Greystone.Greystone'"));
	if (SK_CARDBOARD.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_CARDBOARD.Object);
	}
	static ConstructorHelpers::FClassFinder<URPGGameWarriorAnim> WARRIOR_ANIM(TEXT("AnimBlueprint'/Game/ParagonGreystone/Characters/Heroes/Greystone/Game_Greystone.Game_Greystone_C'"));
	if (WARRIOR_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(WARRIOR_ANIM.Class);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/Materials/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		_CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}

	_CursorToWorld->DecalSize = FVector(16.0f,0.0f, 0.0f);
	_CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());
}

// Called when the game starts or when spawned
void ARPGGameBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	_CursorToWorld->SetActive(false);
	_CursorToWorld->Activate(false);
}

// Called every frame
void ARPGGameBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_CursorToWorld != nullptr)
	{
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (UWorld* World = GetWorld())
			{
				FHitResult HitResult;
				FCollisionQueryParams Params(NAME_None, FCollisionQueryParams::GetUnknownStatId());
				FVector StartLocation = _Camera->GetComponentLocation();
				FVector EndLocation = _Camera->GetComponentRotation().Vector() * 2000.0f;
				Params.AddIgnoredActor(this);
				World->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);
				FQuat SurfaceRotation = HitResult.ImpactNormal.ToOrientationRotator().Quaternion();
				_CursorToWorld->SetWorldLocationAndRotation(HitResult.Location, SurfaceRotation);
			}
		}
		else if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			if (_bInputMove == true)
			{
				_CursorToWorld->SetWorldLocation(_MoveFV);
				_CursorToWorld->SetWorldRotation(_MoveR);
			}
		}
		
		FVector NewScale = FMath::Lerp(_InitDecalSize, _FinishDecalSize, _DecalRatio);
		_CursorToWorld->DecalSize = NewScale;
		_DecalRatio += 0.03f;

		if (_DecalRatio > 1)
		{
			_bInputMove = false;
			_CursorToWorld->SetWorldLocation(FVector::ZeroVector);
			_CursorToWorld->SetWorldRotation(FRotator::ZeroRotator);
		}
	
	}
	
}

// Called to bind functionality to input
void ARPGGameBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ARPGGameBaseCharacter::InitDecalSize()
{
	_CursorToWorld->DecalSize = _InitDecalSize;
	_DecalRatio = 0.f;
}

void ARPGGameBaseCharacter::InitDecalPostionAndRotation(FHitResult result)
{
	FVector CursorFV = result.ImpactNormal;
	_MoveR = CursorFV.Rotation();
	_MoveFV = result.Location;
}

