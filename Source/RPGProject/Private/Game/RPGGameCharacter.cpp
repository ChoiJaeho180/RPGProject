// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/RPGGameCharacter.h"
#include "Game/RPGGameController.h"
#include "Game/Skill/RPGGameAbilityR.h"
#include "Game/Skill/RPGGameAbilityUltimage.h"
#include "Game/RPGGameDataTableManager.h"
#include "Common/RPGCommonGameInstance.h"
#include "Game/RPGGamePlayerState.h"
// Sets default values
ARPGGameCharacter::ARPGGameCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_LevelUpCompo = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("LevelCompo"));
	_LevelUpCompo->SetupAttachment(GetMesh());
	_LevelUpCompo->bAutoActivate = false;
	_BaseAttackRadius = 80.f;
	_BaseAttackRange = 300.f;


	static ConstructorHelpers::FObjectFinder<UParticleSystem> LEVEL_UP_PARTICLE(TEXT("ParticleSystem'/Game/Luos8Elements/Particles/Wind/Par_Lmagic_Wind_Def_01.Par_Lmagic_Wind_Def_01'"));
	if (LEVEL_UP_PARTICLE.Succeeded()) _LevelUpCompo->SetTemplate(LEVEL_UP_PARTICLE.Object);


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

	AbilityR->delegateReadyCoolDownSkill.BindUObject(this, &ARPGGameCharacter::CheckUsableSkill);
	_Skills.Add(AbilityR);
	ARPGGameBaseEffect* AbilityUltimate = GetWorld()->SpawnActor<ARPGGameAbilityUltimage>(AbilityUltimgeClass);
	AbilityUltimate->SetInputKeyIdentify("W");
	AbilityUltimate->SetSpecialState(true);
	AbilityUltimate->Init();
	_Skills.Add(AbilityUltimate);

	_WarriorAnim = Cast<URPGGameWarriorAnim>(GetMesh()->GetAnimInstance());
	_WarriorAnim->Init();

	ARPGGamePlayerState* RPGPlayerState = Cast<ARPGGamePlayerState>(GetController()->PlayerState);
	RPGPlayerState->delegateReadySpecialBar.BindUObject(this, &ARPGGameCharacter::SetUsableSpecialSkill);
	RPGPlayerState->delegateLevelUp.BindUObject(this, &ARPGGameCharacter::LevelUP);
}

void ARPGGameCharacter::InputAttack()
{
	_WarriorAnim->InputAttack();
}

void ARPGGameCharacter::InputSkill(const FString& InputKey)
{
	
	for (int i = 0; i < _Skills.Num(); i++)
	{
		if (_Skills[i]->GetInputKeyIdentify() != InputKey) continue;
			
		if (_Skills[i]->GetESkillState() != ESkillState::READY) return;
		
		ARPGGamePlayerState* RPGPlayerState = Cast<ARPGGamePlayerState>(GetController()->PlayerState);
		if (RPGPlayerState->GetCharacterMP() - _Skills[i]->GetConsumeMP() < 0)
		{
			_Skills[i]->SetESkillState(ESkillState::IMPOSSIBILITY);
			return;
		}
		if (_WarriorAnim->PlaySkill(InputKey) == true)
		{
			RPGPlayerState->AddMP(-_Skills[i]->GetConsumeMP());
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

void ARPGGameCharacter::LevelUP()
{
	_LevelUpCompo->ToggleActive();
}

void ARPGGameCharacter::Resurrection()
{
	_WarriorAnim->SetDead(false);
	GetMesh()->SetCollisionProfileName("Character");
}

void ARPGGameCharacter::CheckUsableSkill()
{
	ARPGGamePlayerState* RPGPlayerState = Cast<ARPGGamePlayerState>(GetController()->PlayerState);
	for (int i = 0; i < _Skills.Num(); i++)
	{
		if (_Skills[i]->GetSpecialState() == true) continue;
		if (RPGPlayerState->GetCharacterMP() - _Skills[i]->GetConsumeMP() < 0)
		{
			_Skills[i]->SetESkillState(ESkillState::IMPOSSIBILITY);
		}
		else
		{
			if (_Skills[i]->GetESkillState() == ESkillState::ING &&
				_Skills[i]->GetCurrentCoolDown() < 0)
			{
				_Skills[i]->SetESkillState(ESkillState::READY);
			}
			else if (_Skills[i]->GetESkillState() == ESkillState::IMPOSSIBILITY)
			{
				_Skills[i]->SetESkillState(ESkillState::READY);
			}
		}
	}
	
	
}

void ARPGGameCharacter::SetUsableSpecialSkill()
{
	UE_LOG(LogTemp, Warning, TEXT("?????"));
	ARPGGamePlayerState* RPGPlayerState = Cast<ARPGGamePlayerState>(GetController()->PlayerState);
	for (int i = 0; i < _Skills.Num(); i++)
	{
		if (_Skills[i]->GetSpecialState() == false) continue;
		if(RPGPlayerState->GetSpecialBar() >= 100) _Skills[i]->SetESkillState(ESkillState::READY);
		else _Skills[i]->SetESkillState(ESkillState::IMPOSSIBILITY);
	}
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

