// Fill out your copyright notice in the Description page of Project Settings.

#include "Common/REST/RPGCommonBaseExecutor.h"

ARPGCommonBaseExecutor::ARPGCommonBaseExecutor()
{

}

void ARPGCommonBaseExecutor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARPGCommonBaseExecutor::Update(TSharedPtr<FJsonObject> RestMsg)
{
	APlayerController* CurrentController = GetWorld()->GetFirstPlayerController();
	//CurrentController->
}

