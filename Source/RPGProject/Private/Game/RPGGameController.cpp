// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/RPGGameController.h"
#include "Common/RPGCommonGameInstance.h"
#include "Game/RPGGameGameMode.h"
#include "Game/UI/RPGGameUIManager.h"
#include "Game/RPGGameCharacter.h"
#include "Game/RPGGamePlayerState.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Components/DecalComponent.h"

ARPGGameController::ARPGGameController()
{
	
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
	
	FInputModeGameAndUI InputMode;
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);
	
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
}

void ARPGGameController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("LeftMouseClick"), EInputEvent::IE_Released, this, &ARPGGameController::LeftMouseClick);
	InputComponent->BindAction(TEXT("Move"), EInputEvent::IE_Pressed, this, &ARPGGameController::Move);
	InputComponent->BindAction<FUIInteractionDelegate>(TEXT("Bag"), EInputEvent::IE_Released, this, &ARPGGameController::InteractionUI, EInventoryUIType::BAG_INVENTORY);
	InputComponent->BindAction<FUIInteractionDelegate>(TEXT("Equipmenet"), EInputEvent::IE_Released, this, &ARPGGameController::InteractionUI, EInventoryUIType::EQUIPMENT_INVENTORY);

	//FString a = "1";
	InputComponent->BindAction<FUIInputActionBarDelegate>(TEXT("Portion_1"), EInputEvent::IE_Pressed, this, &ARPGGameController::InteractionPortionBarUI, FString("1"));
	InputComponent->BindAction<FUIInputActionBarDelegate>(TEXT("Portion_2"), EInputEvent::IE_Pressed, this, &ARPGGameController::InteractionPortionBarUI, FString("2"));
	InputComponent->BindAction<FUIInputActionBarDelegate>(TEXT("Portion_3"), EInputEvent::IE_Pressed, this, &ARPGGameController::InteractionPortionBarUI, FString("3"));
	InputComponent->BindAction<FUIInputActionBarDelegate>(TEXT("Portion_4"), EInputEvent::IE_Pressed, this, &ARPGGameController::InteractionPortionBarUI, FString("4"));
	InputComponent->BindAction<FUIInputActionBarDelegate>(TEXT("Portion_5"), EInputEvent::IE_Pressed, this, &ARPGGameController::InteractionPortionBarUI, FString("5"));
	InputComponent->BindAction<FUIInputActionBarDelegate>(TEXT("Portion_6"), EInputEvent::IE_Pressed, this, &ARPGGameController::InteractionPortionBarUI, FString("6"));
	InputComponent->BindAction<FUIInputActionBarDelegate>(TEXT("Portion_7"), EInputEvent::IE_Pressed, this, &ARPGGameController::InteractionPortionBarUI, FString("7"));
	InputComponent->BindAction<FUIInputActionBarDelegate>(TEXT("Portion_8"), EInputEvent::IE_Pressed, this, &ARPGGameController::InteractionPortionBarUI, FString("8"));
	
}

void ARPGGameController::InitItemData(const TArray<FRPGRestItem>& RestItemData)
{
	_PlayerStat->InitData(RestItemData);
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		_GameUIManager->InitInventory(RestItemData);
	});
	
}

void ARPGGameController::MoveToMouseCursor()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		if (ARPGGameCharacter* MyPawn = Cast<ARPGGameCharacter>(GetPawn()))
		{
			if (MyPawn->GetCursorToWorld())
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());
			}
		}
	}
	else
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);
		if (Hit.bBlockingHit)
		{
			// We hit something, move there
			SetNewMoveDestination(Hit);

		}
	}
}

void ARPGGameController::SetNewMoveDestination(FHitResult Hit)
{
	ARPGGameCharacter* MyPawn = Cast<ARPGGameCharacter>(GetPawn());
	if (MyPawn)
	{
		float const Distance = FVector::Dist(Hit.ImpactPoint, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > MIN_MOVE_DIST))
		{
			MyPawn->InitDecalPostionAndRotation(Hit);
			MyPawn->InitDecalSize();
			MyPawn->SetbInputMove(true);
			MyPawn->OnClikedMove(Hit.ImpactPoint);
		}
	}
}

void ARPGGameController::MovePoint()
{

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

void ARPGGameController::Move()
{
	MoveToMouseCursor();
}

void ARPGGameController::LeftMouseClick()
{

	FHitResult Hit;
	GetHitResultUnderCursor(ECC_GameTraceChannel3, false, Hit);
	if (Hit.bBlockingHit)
	{
		float Distance = FVector::Dist(Hit.Location, _Character->GetActorLocation());
		if (Distance > NPC_TO_CHARACTER_DISTANCE)
			return;
		_GameUIManager->ActiveShop();
	}
}

void ARPGGameController::InteractionUI(EInventoryUIType InteractionType)
{
	UE_LOG(LogTemp, Warning, TEXT("InteractionUI"));
	_GameUIManager->SendInputState(InteractionType);
}

void ARPGGameController::InteractionPortionBarUI(FString Key)
{
	TSharedPtr<FRPGItemInfo> Data = _GameUIManager->GetInputPortionSlotData(Key);
	_PlayerStat->UsePortion(Data);
}
