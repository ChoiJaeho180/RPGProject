// Fill out your copyright notice in the Description page of Project Settings.
#include "Common/REST/RPGCommonCharacterInfoExecutor.h"
#include "Game/RPGGameController.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Common/RPGCommonStringParser.h"

// Sets default values
ARPGCommonCharacterInfoExecutor::ARPGCommonCharacterInfoExecutor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	_RestMsgIdentify = FString("USERINFO");
}

// Called when the game starts or when spawned
void ARPGCommonCharacterInfoExecutor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARPGCommonCharacterInfoExecutor::Update(TSharedPtr<FJsonObject>& RestMsg)
{
	UE_LOG(LogTemp, Warning, TEXT("ARPGCommonCharacterInfoExecutor"));
	auto Field = RestMsg->TryGetField("ResultCode");
	if (Field == nullptr) return;
		
	double a = Field->AsNumber();
	if (a < 0) return;
		
	ARPGGameController* CurrentController = Cast<ARPGGameController>(GetWorld()->GetFirstPlayerController());
	auto CharacterInfo = RestMsg->TryGetField("CharacterInfo");
	auto CharacterArray = CharacterInfo->AsArray();
	TSharedPtr<FCharacterInfo> ResultCharacterInfo = MakeShareable(new FCharacterInfo());

	for (int i = 0; i < CharacterArray.Num(); i++)
	{
		auto result = CharacterArray[i]->AsObject();

		FString PositionInfo = result->TryGetField("LastPosition")->AsString();
		TMap<FString, FString> PositionData = RPGCommonStringParser::StringParsing(PositionInfo);
		ResultCharacterInfo->CurrentPosition = FVector(FCString::Atoi(*PositionData["X"]), FCString::Atoi(*PositionData["Y"]), FCString::Atoi(*PositionData["Z"]));
		ResultCharacterInfo->CurrentVillage = PositionData["Map"];

		ResultCharacterInfo->Job = result->TryGetField("Job")->AsString();
		FString Stat = result->TryGetField("Stat")->AsString();
		TMap<FString, FString> StatResult = RPGCommonStringParser::StringParsing(Stat);
		ResultCharacterInfo->Stat = StatResult;

		FString ItemInfo = result->TryGetField("Items")->AsString();
		TArray<FString> ResultCommaParsing = RPGCommonStringParser::CommaStringParsing(ItemInfo);
		TMap<FString, FString> MoneyData = RPGCommonStringParser::SingleStringParsing(ResultCommaParsing[0]);
		if(ResultCommaParsing.Num() != 0) ResultCommaParsing.RemoveAt(0);
		TArray<FRPGRestItem> ItemData = RPGCommonStringParser::ItemsDataParsing(ResultCommaParsing);

		// ActionBar ?????????????????? ?????? portion?????? ??????????????????
		FString ActionBar_Portion = result->TryGetField("ActionBar")->IsNull() == true ? "" : result->TryGetField("ActionBar")->AsString();
		TArray<FString> ActionBarCommaParsing = RPGCommonStringParser::CommaStringParsing(ActionBar_Portion);
		TArray<FRPGRestItem> ActionBarData = RPGCommonStringParser::ItemsDataParsing(ActionBarCommaParsing);

		CurrentController->SetCharacterInfo(ResultCharacterInfo);
		CurrentController->InitItemData(ItemData, ActionBarData, MoneyData);
	}

}

