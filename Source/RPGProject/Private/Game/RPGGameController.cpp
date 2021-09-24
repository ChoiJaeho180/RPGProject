// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/RPGGameController.h"
#include "Common/RPGCommonGameInstance.h"
#include "Game/RPGGameGameMode.h"
#include "Game/UI/RPGGameUIManager.h"

ARPGGameController::ARPGGameController()
{
	PrimaryActorTick.bCanEverTick = true;

	RPGGameUIManagerClass = ARPGGameUIManager::StaticClass();

	bShowMouseCursor = true;
}
void ARPGGameController::BeginPlay()
{
	Super::BeginPlay();
	//
	//SendActiveMap("Game_Village");
	_GameUIManager->Initialize(this);
	AsyncTask(ENamedThreads::AnyThread, [=]()
	{
		URPGCommonGameInstance* CurrentGI = Cast<URPGCommonGameInstance>(GetGameInstance());
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
		JsonObject->SetStringField("Name", CurrentGI->GetCharacterName());
		CurrentGI->PostRequest("/game/getuserinfo", JsonObject);
	});

	SetInputMode(FInputModeGameOnly());
	
}

void ARPGGameController::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void ARPGGameController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	_GameUIManager = GetWorld()->SpawnActor<ARPGGameUIManager>(RPGGameUIManagerClass);
	
}

void ARPGGameController::SendActiveMap(const FString& MapName)
{
	ARPGGameGameMode* GM = Cast<ARPGGameGameMode>(GetWorld()->GetAuthGameMode());
	GM->ActiveMap(MapName);
}

void ARPGGameController::SetCharacterInfo(TSharedPtr<FCharacterInfo>& NewCharacterInfo)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		SendActiveMap(NewCharacterInfo->CurrentVillage);
		GetPawn()->SetActorLocation(NewCharacterInfo->CurrentPosition);
		_GameUIManager->UpdateLevel();
	});
}

