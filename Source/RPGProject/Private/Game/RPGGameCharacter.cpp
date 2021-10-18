// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/RPGGameCharacter.h"
#include "Game/RPGGameController.h"
#include "Game/Skill/RPGGameAbilityR.h"
#include "Game/Skill/RPGGameAbilityUltimage.h"
#include "Game/RPGGameDataTableManager.h"
#include "Common/RPGCommonGameInstance.h"

// Sets default values
ARPGGameCharacter::ARPGGameCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_BaseAttackRadius = 80.f;
	_BaseAttackRange = 300.f;

	AbilityRClass = ARPGGameAbilityR::StaticClass();
	AbilityUltimgeClass = ARPGGameAbilityUltimage::StaticClass();
}

// Called when the game starts or when spawned
void ARPGGameCharacter::BeginPlay()
{
	Super::BeginPlay();
	//	
	ARPGGameBaseEffect* AbilityR = GetWorld()->SpawnActor<ARPGGameAbilityR>(AbilityRClass);
	AbilityR->SetInputKeyIdentify("Q");
	AbilityR->Init();
	_Skills.Add(AbilityR);
	ARPGGameBaseEffect* AbilityUltimate = GetWorld()->SpawnActor<ARPGGameAbilityUltimage>(AbilityUltimgeClass);
	AbilityUltimate->SetInputKeyIdentify("W");
	AbilityUltimate->Init();
	_Skills.Add(AbilityUltimate);

	_WarriorAnim = Cast<URPGGameWarriorAnim>(GetMesh()->GetAnimInstance());
	_WarriorAnim->Init();
}

void ARPGGameCharacter::InputAttack()
{
	_WarriorAnim->InputAttack();
}

void ARPGGameCharacter::InputSkill(const FString& InputKey)
{
	for (int i = 0; i < _Skills.Num(); i++)
	{
		if (_Skills[i]->GetInputKeyIdentify() != InputKey)
			continue;
		if (_Skills[i]->CheckUsableSkill() == false)
			return;

		// 쿨타임 체크 적용해야함
		if (_WarriorAnim->PlaySkill(InputKey) == true)
		{
			SetbInvincibility(true);
			_UseCurrentSkill = _Skills[i];
			_Skills[i]->ApplyProperty(this);
			_WarriorAnim->SetWarriorAnimType(EWarriorAnimType::SKILL);
		}
	}

	
}

void ARPGGameCharacter::OnClikedMove(FVector_NetQuantize MovePoint)
{
	if (_WarriorAnim->GetWarriorAnimType() == EWarriorAnimType::SKILL) return;
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
	if (_bInvincibility == true) return;

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

void ARPGGameCharacter::Test(bool test1)
{
	GetMesh()->SetVisibility(test1);
	GetMesh()->bHiddenInGame = !test1;
	UE_LOG(LogTemp, Warning, TEXT("Test"));
}

// Called to bind functionality to input
void ARPGGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//PlayerInputComponent->BindAction(TEXT("LeftMouseClick"), EInputEvent::IE_Released, this, &ARPGGameCharacter::LeftMouseClick);
}

