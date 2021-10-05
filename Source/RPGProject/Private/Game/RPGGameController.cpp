// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/RPGGameController.h"
#include "Common/RPGCommonGameInstance.h"
#include "Game/RPGGameGameMode.h"
#include "Game/UI/RPGGameUIManager.h"
#include "Game/RPGGameCharacter.h"
#include "Game/RPGGamePlayerState.h"
#include "Game/RPGGameCharacterBagComponent.h"

ARPGGameController::ARPGGameController()
{
	PrimaryActorTick.bCanEverTick = true;

	RPGGameUIManagerClass = ARPGGameUIManager::StaticClass();

	bShowMouseCursor = true;
}
void ARPGGameController::BeginPlay()
{
	Super::BeginPlay();
	_Character = Cast<ARPGGameCharacter>(GetPawn());
	_GameUIManager->Initialize(this);
	AsyncTask(ENamedThreads::AnyThread, [=]()
	{
		URPGCommonGameInstance* CurrentGI = Cast<URPGCommonGameInstance>(GetGameInstance());
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
		JsonObject->SetStringField("Name", CurrentGI->GetCharacterName());
		CurrentGI->PostRequest("/game/getuserinfo", JsonObject);
	});
	
	SetInputMode(FInputModeGameAndUI());
	
}

void ARPGGameController::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void ARPGGameController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	_GameUIManager = GetWorld()->SpawnActor<ARPGGameUIManager>(RPGGameUIManagerClass);
	_PlayerStat = GetPlayerState<ARPGGamePlayerState>();
	//_PlayerStat->GetCharacterBag()->TestInfo();
}

void ARPGGameController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis(TEXT("MoveForward"), this, &ARPGGameController::MoveForward);
	InputComponent->BindAxis(TEXT("MoveRight"), this, &ARPGGameController::MoveRight);

	InputComponent->BindAction(TEXT("LeftMouseClick"), EInputEvent::IE_Released, this, &ARPGGameController::LeftMouseClick);
	InputComponent->BindAction<FUIInteractionDelegate>(TEXT("Bag"), EInputEvent::IE_Released, this, &ARPGGameController::InteractionUI, EInventoryUIType::BAG_INVENTORY);
	InputComponent->BindAction<FUIInteractionDelegate>(TEXT("Equipmenet"), EInputEvent::IE_Released, this, &ARPGGameController::InteractionUI, EInventoryUIType::EQUIPMENT_INVENTORY);
}

void ARPGGameController::InitItemData(const TArray<FRPGRestItem>& RestItemData)
{
	_PlayerStat->InitData(RestItemData);
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		_GameUIManager->InitInventory(RestItemData);

	});
	//_PlayerStat
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

void ARPGGameController::MoveForward(float NewAxisValue)
{
	if (NewAxisValue == 0.0f)
		return;

	_Character->MoveForward(NewAxisValue);
}

void ARPGGameController::MoveRight(float NewAxisValue)
{
	if (NewAxisValue == 0.0f)
		return;
	
	_Character->MoveRight(NewAxisValue);
}

void ARPGGameController::LeftMouseClick()
{
	UE_LOG(LogTemp, Warning, TEXT("LeftMouseClick"));
	auto test = _PlayerStat->GetCharacterStat();
	test->TimeStamp++;
	test->SpecialState += 10;


	FHitResult Hit;
	GetHitResultUnderCursor(ECC_GameTraceChannel3, false, Hit);
	if (Hit.bBlockingHit)
	{
		float Distance = FVector::Dist(Hit.Location, _Character->GetActorLocation());
		if (Distance > NPC_TO_CHARACTER_DISTANCE)
			return;

		UE_LOG(LogTemp, Warning, TEXT("wwww"));
		// 충돌 결과가 있을 때의 처리
	}
}

void ARPGGameController::InteractionUI(EInventoryUIType InteractionType)
{
	UE_LOG(LogTemp, Warning, TEXT("InteractionUI"));
	_GameUIManager->SendInputState(InteractionType);
}
