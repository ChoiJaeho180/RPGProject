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
	
}

// Called every frame
void ARPGGameBaseEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ARPGGameBaseEffect::CheckUsableSkill()
{
	if (_CurrentCoolDown >= _CoolDown) return true;
	return false;
}

