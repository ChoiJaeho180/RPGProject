// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/RPGGameGameMode.h"
#include "Game/RPGGameController.h"
#include "Game/RPGGameCharacter.h"
#include "Common/RPGCommonGameInstance.h"
#include "Game/RPGGameMapInfo.h"

ARPGGameGameMode::ARPGGameGameMode()
{
	PlayerControllerClass = ARPGGameController::StaticClass();
	DefaultPawnClass = ARPGGameCharacter::StaticClass();
	MapInfoClass = URPGGameMapInfo::StaticClass();
}

void ARPGGameGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	_MapInfo.Add("Game_Village", NewObject<URPGGameMapInfo>());

	URPGCommonGameInstance* GameInstance = Cast<URPGCommonGameInstance>(GetGameInstance());
	GameInstance->Init();

}

void ARPGGameGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	URPGCommonGameInstance* GameInstance = Cast<URPGCommonGameInstance>(GetGameInstance());
	GameInstance->Release();
}

void ARPGGameGameMode::ActiveMap(const FString& MapName)
{
	FLatentActionInfo info;
	if (_CurrentMapName.IsEmpty() == false)
	{
		UGameplayStatics::UnloadStreamLevel(this, FName(*_CurrentMapName), info, true);
	}
	_CurrentMapName = MapName;
	UGameplayStatics::LoadStreamLevel(this, FName(*_CurrentMapName), true, true, info);
}
