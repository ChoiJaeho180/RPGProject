// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/RPGGameController.h"
#include "Common/RPGCommonGameInstance.h"
#include "Game/RPGGameGameMode.h"

ARPGGameController::ARPGGameController()
{
	PrimaryActorTick.bCanEverTick = true;

	bShowMouseCursor = true;
}
void ARPGGameController::BeginPlay()
{
	Super::BeginPlay();

	AsyncTask(ENamedThreads::AnyThread, [=]()
	{
		URPGCommonGameInstance* CurrentGI = Cast<URPGCommonGameInstance>(GetGameInstance());
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
		JsonObject->SetStringField("Name", CurrentGI->GetCharacterName());
		CurrentGI->PostRequest("/game/getuserinfo", JsonObject);
	});

	SetInputMode(FInputModeGameOnly());
	
}

void ARPGGameController::SendActiveMap(const FString& MapName)
{
	ARPGGameGameMode* GM = Cast<ARPGGameGameMode>(GetWorld()->GetAuthGameMode());
	GM->ActiveMap(MapName);
}

void ARPGGameController::SetCharacterInfo(TSharedPtr<FCharacterInfo>& NewCharacterInfo)
{
	SendActiveMap(NewCharacterInfo->CurrentVillage);
	GetPawn()->SetActorLocation(NewCharacterInfo->CurrentPosition);
}
