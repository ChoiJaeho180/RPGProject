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
#include "Kismet/KismetMathLibrary.h"
#include "Common/REST/RPGCommonSerializeData.h"
#include "Game/Animation/RPGGameWarriorAnim.h"
#include "Game/RPGGameItemStruct.h"
#include "Game/RPGGameDataCopy.h"


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
	InputComponent->BindAction<FUIInteractionDelegate>(TEXT("Stat"), EInputEvent::IE_Released, this, &ARPGGameController::InteractionUI, EInventoryUIType::STAT_INVENTORY);

	InputComponent->BindAction<FUIInputActionBarDelegate>(TEXT("Portion_1"), EInputEvent::IE_Pressed, this, &ARPGGameController::InteractionPortionBarUI, FString("1"));
	InputComponent->BindAction<FUIInputActionBarDelegate>(TEXT("Portion_2"), EInputEvent::IE_Pressed, this, &ARPGGameController::InteractionPortionBarUI, FString("2"));
	InputComponent->BindAction<FUIInputActionBarDelegate>(TEXT("Portion_3"), EInputEvent::IE_Pressed, this, &ARPGGameController::InteractionPortionBarUI, FString("3"));
	InputComponent->BindAction<FUIInputActionBarDelegate>(TEXT("Portion_4"), EInputEvent::IE_Pressed, this, &ARPGGameController::InteractionPortionBarUI, FString("4"));
	InputComponent->BindAction<FUIInputActionBarDelegate>(TEXT("Portion_5"), EInputEvent::IE_Pressed, this, &ARPGGameController::InteractionPortionBarUI, FString("5"));
	InputComponent->BindAction<FUIInputActionBarDelegate>(TEXT("Portion_6"), EInputEvent::IE_Pressed, this, &ARPGGameController::InteractionPortionBarUI, FString("6"));
	InputComponent->BindAction<FUIInputActionBarDelegate>(TEXT("Portion_7"), EInputEvent::IE_Pressed, this, &ARPGGameController::InteractionPortionBarUI, FString("7"));
	InputComponent->BindAction<FUIInputActionBarDelegate>(TEXT("Portion_8"), EInputEvent::IE_Pressed, this, &ARPGGameController::InteractionPortionBarUI, FString("8"));

	InputComponent->BindAction<FUIInputActionBarDelegate>(TEXT("Skill_Q"), EInputEvent::IE_Pressed, this, &ARPGGameController::InputSkills, FString("Q"));
	InputComponent->BindAction<FUIInputActionBarDelegate>(TEXT("Skill_W"), EInputEvent::IE_Pressed, this, &ARPGGameController::InputSkills, FString("W"));
	InputComponent->BindAction(TEXT("Portal"), EInputEvent::IE_Released, this, &ARPGGameController::PreChangeMap);
}

void ARPGGameController::InitItemData(const TArray<FRPGRestItem>& RestItemData, const TArray<FRPGRestItem>& RestActionBar, const TMap<FString, FString>& MoneyData)
{
	_PlayerStat->InitData(RestItemData, MoneyData);
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		_GameUIManager->InitInventoryAndActionBar(RestItemData, RestActionBar);
	});
	
}

void ARPGGameController::UpdateCharacterInfoToDB(TArray<TSharedPtr<FRPGItemSlot>>& BagData, const TArray<TSharedPtr<FRPGItemSlot>>& PortionSlotData)
{
	ARPGGameGameMode* GM = Cast<ARPGGameGameMode>(GetWorld()->GetAuthGameMode());
	URPGCommonGameInstance* GameInstance = Cast<URPGCommonGameInstance>(GetGameInstance());
	
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	// Position Data
	FString LastPosition = URPGCommonSerializeData::GetLastPosition(_Character->GetCurrentMap(), GetPawn()->GetActorLocation());
	JsonObject->SetStringField("LastPosition", LastPosition);
	// Bag Data
	int CurrentMoney = _PlayerStat->GetCharacterBag()->GetCharacterMoney()->Money;
	FString MoneyData = URPGCommonSerializeData::GetMoney(CurrentMoney);
	for (int i = 0; i < BagData.Num(); i++)
	{
		auto Item = _PlayerStat->GetFindItem(BagData[i]->Name);
		if (Item == nullptr)
		{
			auto RemoveItem = BagData[i];
			BagData.Remove(RemoveItem);
			continue;
		}
		BagData[i]->Count = Item->Count;
	}
	
	FString ItemData = URPGCommonSerializeData::GetItemsData(BagData);
	if (ItemData.Len() != 0) MoneyData = MoneyData + ",";
	FString Items = MoneyData + ItemData;
	JsonObject->SetStringField("Items", Items);

	FString PortionSlot = URPGCommonSerializeData::GetItemsData(PortionSlotData);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *PortionSlot);
	if(PortionSlot.IsEmpty() == false)JsonObject->SetStringField("ActionBar", PortionSlot);

	FString Stat = URPGCommonSerializeData::GetCharacterStat(_PlayerStat->GetCharacterStat()->Stat);
	JsonObject->SetStringField("Stat", Stat);
	JsonObject->SetStringField("CharacterName", GameInstance->GetCharacterName());
	GameInstance->PostRequest("/game/updatecharacterinfo", JsonObject);

	ARPGGameNPCQuest* NPC = GM->GetQuest();
	TArray<int> Index = NPC->GetComplateQuestIndex();

	if (Index.Num() == 0) return;
	TSharedPtr<FJsonObject> JsonObject2 = MakeShareable(new FJsonObject);
	FString ClearQuestString;
	for (int i = 0; i < Index.Num(); i++)
	{
		ClearQuestString += FString::FromInt(Index[i]) + ",";
	}
	ClearQuestString.RemoveAt(ClearQuestString.Len() - 1); 

	JsonObject->SetStringField("ClearQuestIndex", ClearQuestString);
	JsonObject2->SetStringField("CharacterName", GameInstance->GetCharacterName());
	GameInstance->PostRequest("/game/updatequestinfo", JsonObject2);


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

void ARPGGameController::SendActiveMap(const FString& MapName)
{
	//_Character->SetCurrentMap(MapName);
	ARPGGameGameMode* GM = Cast<ARPGGameGameMode>(GetWorld()->GetAuthGameMode());
	GM->ActiveMap(MapName, _Character);
}

void ARPGGameController::SetCharacterInfo(TSharedPtr<FCharacterInfo>& NewCharacterInfo)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		_PlayerStat->GetCharacterStat()->SetInfo(NewCharacterInfo->Stat);
		SendActiveMap(NewCharacterInfo->CurrentVillage);
		GetPawn()->SetActorLocation(NewCharacterInfo->CurrentPosition);
		_Character->SetUsableSpecialSkill();
		_Character->CheckUsableSkill();
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
		ARPGGameNPCQuest* NPC = Cast<ARPGGameNPCQuest>(Hit.Actor);
		if (NPC == nullptr)
		{
			_GameUIManager->ActiveShop();
		}
		else
		{
			FRPGQuestInfo QuestInfo = NPC->GetCurrentQuest();
			EGameQuestNPCState State = NPC->GetCurrentQuestNPCState();

			if (State == EGameQuestNPCState::ING_YET)
			{
				State = NPC->UpdateQuestState(_PlayerStat->GetQuestQuickInfo());
			}
			else if (State == EGameQuestNPCState::ING_COMPLATE)
			{
				FRPGQuestInfo CurrentQuestInfo = NPC->GetCurrentQuest();
				for (auto& item : CurrentQuestInfo.Compensation)
				{
					_PlayerStat->AddState(item.Key, item.Value);
				}
				FRPGQuestQuickInfo EnemyInfo;
				_PlayerStat->UpdateQuestQuickInfo(EnemyInfo);
				NPC->ComplateQuest();
				NPC->GetQuest();
			}
			_GameUIManager->ActiveQuestUI(QuestInfo, State);
		}
	}
	FHitResult Hit2;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit2);
	if (Hit2.bBlockingHit)
	{
		FRotator rotation = UKismetMathLibrary::FindLookAtRotation(GetPawn()->GetActorLocation(), Hit2.Location);
		_Character->SetRotationRow(rotation);
	}
	ARPGGameGameMode* GM = Cast<ARPGGameGameMode>(GetWorld()->GetAuthGameMode());
	if (_Character->GetCurrentMap() == GM->GetCantAttackMap()) return;
	_Character->InputAttack();
	_PlayerStat->AddSpecialBar(100);
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
	_Character->CheckUsableSkill();
}

void ARPGGameController::InputSkills(FString Key)
{
	ARPGGameGameMode* GM = Cast<ARPGGameGameMode>(GetWorld()->GetAuthGameMode());
	if (_Character->GetCurrentMap() == GM->GetCantAttackMap()) return;

	_Character->InputSkill(Key);
}

void ARPGGameController::PreChangeMap()
{
	if (_Character->GetNextMap() == FString("")) return;
	
	_GameUIManager->SetFadeEffectType(ECommonFadeState::FADE_IN, true);
	_GameUIManager->UpdateLevel();
}

void ARPGGameController::ComplateChangeMap()
{
	ARPGGameGameMode* GM = Cast<ARPGGameGameMode>(GetWorld()->GetAuthGameMode());
	if (_Character->GetAnim()->GetDead() == true)
	{
		_Character->Resurrection();
		_PlayerStat->AddHP(50);
	}
	
	_GameUIManager->SetFadeEffectType(ECommonFadeState::FADE_OUT, true);
	_GameUIManager->UpdateLevel();
}

void ARPGGameController::ChangeMap()
{
	ARPGGameGameMode* GM = Cast<ARPGGameGameMode>(GetWorld()->GetAuthGameMode());
	GM->ActiveMap(_Character->GetNextMap(), _Character);
}

void ARPGGameController::OnFinishChangeMapEffect()
{
	URPGCommonGameInstance* CurrentGI = Cast<URPGCommonGameInstance>(GetGameInstance());
	auto DataCopy = CurrentGI->GetDataCopyClass();
	DataCopy->SetUpdateMapName(_Character->GetCurrentMap());
}

void ARPGGameController::AddExp(int Exp, bool bAddLog)
{
	_PlayerStat->AddExp(Exp, bAddLog);
}
void ARPGGameController::AddGold(int Gold, bool bAddLog)
{
	_PlayerStat->AddGold(Gold, bAddLog);
}

void ARPGGameController::SendQuestInfoToPlayerState(FRPGQuestQuickInfo& QuestQuickInfo)
{
	_PlayerStat->UpdateQuestQuickInfo(QuestQuickInfo);
	ARPGGameGameMode* GM = Cast<ARPGGameGameMode>(GetWorld()->GetAuthGameMode());
	ARPGGameNPCQuest* NPC =  GM->GetQuest();
	NPC->SetCurrentQuestNPCState(EGameQuestNPCState::ING_YET);
}

void ARPGGameController::CheckAddQuest(EEnemyType EnemyType)
{
	if (_PlayerStat->CheckQuestQuickInfo(EnemyType))
	{
		ARPGGameGameMode* GM = Cast<ARPGGameGameMode>(GetWorld()->GetAuthGameMode());
		auto QuestNPC = GM->GetQuest();
		QuestNPC->SetCurrentQuestNPCState(EGameQuestNPCState::ING_COMPLATE);
	}
}

