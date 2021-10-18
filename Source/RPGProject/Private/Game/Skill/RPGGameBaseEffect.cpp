// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Skill/RPGGameBaseEffect.h"

// Sets default values
ARPGGameBaseEffect::ARPGGameBaseEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARPGGameBaseEffect::BeginPlay()
{
	Super::BeginPlay();
	//SetESkillState(ESkillState::IMPOSSIBILITY);
}

// Called every frame
void ARPGGameBaseEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_SkillState != ESkillState::ING) return;
	if (_bSpecialSkill == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("ARPGGameBaseEffect"));
		SetESkillState(ESkillState::IMPOSSIBILITY);
	}
	if (_CurrentCoolDown <= 0)
	{
		delegateReadyCoolDownSkill.ExecuteIfBound();
		return;
	}

	_CurrentCoolDown -= DeltaTime;
	_TimeStamp++;
}


