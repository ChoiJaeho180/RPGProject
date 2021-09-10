// Fill out your copyright notice in the Description page of Project Settings.
#include "Common/REST/RPGCommonNewCharacterExecutor.h"
#include "Intro/RPGIntroController.h"

ARPGCommonNewCharacterExecutor::ARPGCommonNewCharacterExecutor()
{
	_RestMsgIdentify = FString("NEWCHARACTER");
}

void ARPGCommonNewCharacterExecutor::BeginPlay()
{
	Super::BeginPlay();

}
void ARPGCommonNewCharacterExecutor::Update(TSharedPtr<FJsonObject>& RestMsg)
{
	auto Field = RestMsg->TryGetField("ResultCode");
	if (Field == nullptr)
		return;
	FString resultState = Field->AsString();
	ARPGIntroController* CurrentController = Cast<ARPGIntroController>(GetWorld()->GetFirstPlayerController());
	if (resultState == SUCCESSD_REST_API)
	{

	}
	else
	{

	}

}