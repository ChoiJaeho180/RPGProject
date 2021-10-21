// Fill out your copyright notice in the Description page of Project Settings.
#include "Common/RPGCommonGameInstance.h"
#include "Common/REST/RPGCommonRestManager.h"
#include "Game/RPGGameNPCData.h"
#include "Game/RPGGameDataCopy.h"
#include "Game/RPGGameDataTableManager.h"
#include "Blueprint/UserWidget.h"

URPGCommonGameInstance::URPGCommonGameInstance()
{
	RestManagerClass = ARPGCommonRestManager::StaticClass();
	RPGGameClass = ARPGGameNPCData::StaticClass();
	GameDataCopyClass = ARPGGameDataCopy::StaticClass();

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_WARRIOR(TEXT("SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Meshes/Greystone.Greystone'"));
	if (SK_WARRIOR.Succeeded()) CharacterSkeletalMeshObject = SK_WARRIOR.Object;

	static ConstructorHelpers::FClassFinder<UUserWidget>SLOT_WIDGET(TEXT("WidgetBlueprint'/Game/InventorySystem/UI/Blueprints/Inventory/Inventory_Slot.Inventory_Slot_C'"));
	if (SLOT_WIDGET.Succeeded()) RPGSlotClass = SLOT_WIDGET.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget>ACTION_BAR_SLOT_WIDGET(TEXT("WidgetBlueprint'/Game/UI_Kit/Widgets/ActionBars/ActionbarSlot_T4.ActionbarSlot_T4_C'"));
	if (ACTION_BAR_SLOT_WIDGET.Succeeded()) RPGActionBarSlotClass = ACTION_BAR_SLOT_WIDGET.Class;


	static ConstructorHelpers::FClassFinder<UUserWidget>SELL_HELPER_WIDGET(TEXT("WidgetBlueprint'/Game/Blueprints/GameWidgetBP/Character/ShopSellHelperLayout.ShopSellHelperLayout_C'"));
	if (SELL_HELPER_WIDGET.Succeeded())RPGSellHelperClass = SELL_HELPER_WIDGET.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget>BUY_HELPER_WIDGET(TEXT("WidgetBlueprint'/Game/Blueprints/GameWidgetBP/Character/ShopBuylHelperLayout.ShopBuylHelperLayout_C'"));
	if (BUY_HELPER_WIDGET.Succeeded()) RPGBuyHelperClass = BUY_HELPER_WIDGET.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget>QUEST_QUICK_WIDGET(TEXT("WidgetBlueprint'/Game/Blueprints/GameWidgetBP/Character/QuestQuickLayout.QuestQuickLayout_C'"));
	if (QUEST_QUICK_WIDGET.Succeeded())RPGQuestQuickClass = QUEST_QUICK_WIDGET.Class;
	static ConstructorHelpers::FClassFinder<UUserWidget>ItemToolTip(TEXT("WidgetBlueprint'/Game/Blueprints/GameWidgetBP/Character/SlotToolTip.SlotToolTip_C'"));
	if(ItemToolTip.Succeeded())ItemToolTipClass = ItemToolTip.Class;
	//UBlueprintGeneratedClass* ItemToolTip = LoadObject<UBlueprintGeneratedClass>(nullptr,);
	//ItemToolTipClass = Cast<UClass>(ItemToolTip);
}

void URPGCommonGameInstance::Init()
{
	if (_RestManager != nullptr)
	{
		GetWorld()->DestroyActor(_RestManager);
	}

	if (_DataTableManager == nullptr)
	{
		_DataTableManager = NewObject<URPGGameDataTableManager>();
		_DataTableManager->Init();
	}

	_RestManager = GetWorld()->SpawnActor<ARPGCommonRestManager>(RestManagerClass);
	if (_TempToken.IsEmpty() == false)
	{
		_RestManager->SetToken(_TempToken);
		_TempToken = nullptr;
	}
}

bool URPGCommonGameInstance::PostRequest(FString URL, TSharedPtr<FJsonObject>& JsonObject)
{
	_RestManager->PostRequest(URL, JsonObject);
	return false;
}

void URPGCommonGameInstance::Release()
{
	_TempToken = _RestManager->GetToken();
	_RestManager->Release();
}

void URPGCommonGameInstance::CreateGameNPCData()
{
	if (_GameNPCData != nullptr)
		return;
	_GameNPCData = GetWorld()->SpawnActor<ARPGGameNPCData>(RPGGameClass);
}

void URPGCommonGameInstance::CreateGameDataCopyClass()
{
	if (_GameDataCopy != nullptr)
		return;
	
	_GameDataCopy = GetWorld()->SpawnActor<ARPGGameDataCopy>(GameDataCopyClass);
}
