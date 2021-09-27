// Fill out your copyright notice in the Description page of Project Settings.
#include "Intro/RPGIntroGameMode.h"
#include "Intro/RPGIntroController.h"
#include "Intro/RPGIntroCharacter.h"
#include "Common/RPGCommonGameInstance.h"
#include "Intro/RPGIntroLobbyScarecrow.h"
#include "GameFramework/PlayerStart.h"

ARPGIntroGameMode::ARPGIntroGameMode()
{
	PlayerControllerClass = ARPGIntroController::StaticClass();
	DefaultPawnClass = ARPGIntroCharacter::StaticClass();
	LobbyScarecrowClass = ARPGIntroLobbyScarecrow::StaticClass();

	_PlayerStartPoint.Add(EIntroUIWidgetState::MAIN, FString("Main_PlayerStart"));
	_PlayerStartPoint.Add(EIntroUIWidgetState::LOBBY, FString("Lobby_PlayerStart"));
	_LobbyScarecrowsPoint.Add(FTransform(FRotator(0, 90, 0), FVector(-4530, -360, 170)));
	_LobbyScarecrowsPoint.Add(FTransform(FRotator(0, 90, 0), FVector(-4530, -80, 170)));
	_LobbyScarecrowsPoint.Add(FTransform(FRotator(0, 90, 0), FVector(-4530, 200, 170)));
}

void ARPGIntroGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	_IntroController = Cast<ARPGIntroController>(NewPlayer);
}

void ARPGIntroGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	URPGCommonGameInstance* GameInstance = Cast<URPGCommonGameInstance>(GetGameInstance());
	if (_bNormalLevelTransform == false)
	{
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
		GameInstance->PostRequest("/users/logout", JsonObject);
	}
	GameInstance->Release();
}

void ARPGIntroGameMode::SetPlayerStart(EIntroUIWidgetState NewState)
{
	if (_PlayerStartPoint.Contains(NewState) == false)
		return;
	AActor* PlayerStart = FindPlayerStart(_IntroController, _PlayerStartPoint[NewState]);
	_IntroController->GetPawn()->SetActorRelativeTransform(PlayerStart->GetActorTransform());

}

void ARPGIntroGameMode::CreateLobbyScarecrow(const TArray<TSharedPtr<FJsonValue>>& Info)
{
	AsyncTask(ENamedThreads::GameThread,[=]()
	{
		for (int i = 0; i < Info.Num(); i++)
		{
			int index = _IntroLobbyScarecrows.Num();
			_IntroLobbyScarecrows.Add(GetWorld()->SpawnActor<ARPGIntroLobbyScarecrow>(LobbyScarecrowClass));
			_IntroLobbyScarecrows[index]->SetActorTransform(_LobbyScarecrowsPoint[index]);
		}
	});

}

void ARPGIntroGameMode::UpdateChooseAnim(const int& ScarecrowIndex)
{
	_IntroLobbyScarecrows[ScarecrowIndex]->UpdateChooseAnim(true);
}

void ARPGIntroGameMode::ChangeLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), "PersistentGameLevel");
	_bNormalLevelTransform = true;
}
