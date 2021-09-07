// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/REST/RPGCommonRestLoginExecutor.h"

// Sets default values
ARPGCommonRestLoginExecutor::ARPGCommonRestLoginExecutor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	_RestMsgIdentify = FString("LOGIN");
}

// Called when the game starts or when spawned
void ARPGCommonRestLoginExecutor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARPGCommonRestLoginExecutor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARPGCommonRestLoginExecutor::Update(TSharedPtr<FJsonObject> RestMsg)
{

}

