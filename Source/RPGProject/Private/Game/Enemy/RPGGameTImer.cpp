// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Enemy/RPGGameTImer.h"

// Sets default values for this component's properties
URPGGameTImer::URPGGameTImer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URPGGameTImer::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URPGGameTImer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (_bActive == false) return;
		
	_CurrentTime += DeltaTime;
	if (_StandardTime > _CurrentTime) return;

	delegateAchieveTime.ExecuteIfBound();
	_bActive = false;
}

void URPGGameTImer::SetStandardTime(float Time)
{
	_StandardTime = Time;
	_CurrentTime = 0;
	_bActive = true;
}

