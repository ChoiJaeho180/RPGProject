// Fill out your copyright notice in the Description page of Project Settings.
#include "Common/REST/RPGCommonNPCInfoExecutor.h"
#include "Common/RPGCommonGameInstance.h"
#include "Game/RPGGameController.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Common/RPGCommonStringParser.h"
#include "Game/RPGGameNPCData.h"
#include "Game/RPGGameGameMode.h"

// Sets default values
ARPGCommonNPCInfoExecutor::ARPGCommonNPCInfoExecutor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	_RestMsgIdentify = FString("NPCINFO");
}

// Called when the game starts or when spawned
void ARPGCommonNPCInfoExecutor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARPGCommonNPCInfoExecutor::Update(TSharedPtr<FJsonObject>& RestMsg)
{
	auto Field = RestMsg->TryGetField("ResultCode");
	if (Field == nullptr)
		return;
	FString resultState = Field->AsString();
	if (resultState == SUCCESSD_REST_API)
	{
		auto CharacterInfo = RestMsg->TryGetField("NPCInfo");
		if (CharacterInfo == nullptr)
			return;
		auto CharacterArray = CharacterInfo->AsArray();
		ARPGGameController* CurrentController = Cast<ARPGGameController>(GetWorld()->GetFirstPlayerController());
		ARPGGameGameMode* GM = Cast<ARPGGameGameMode>(GetWorld()->GetAuthGameMode());
		URPGCommonGameInstance* GI = Cast<URPGCommonGameInstance>(GetGameInstance());
		ARPGGameNPCData* NPCData = GI->GetGameNPCData();
		AsyncTask(ENamedThreads::GameThread, [=]()
		{
			for (int i = 0; i < CharacterArray.Num(); i++)
			{
				auto result = CharacterArray[i]->AsObject();

				FString PositionInfo = result->TryGetField("position")->AsString();
				TMap<FString, FString> PositionData = RPGCommonStringParser::StringParsing(PositionInfo);
				FNPCInfo NewNPCInfo;
				NewNPCInfo.Position = FVector(FCString::Atoi(*PositionData["X"]), FCString::Atoi(*PositionData["Y"]), FCString::Atoi(*PositionData["Z"]));
				NewNPCInfo.Village = PositionData["Map"];
				NewNPCInfo.Name = result->TryGetField("name")->AsString();
				NewNPCInfo.Type = result->TryGetField("type")->AsString();
				FString Speech = result->TryGetField("Speech")->AsString();
				NewNPCInfo.Speech = RPGCommonStringParser::CommaStringParsing(Speech);
				NewNPCInfo.bQuest = result->TryGetField("Quest")->AsNumber() > 0 ? true : false;
				NPCData->SetNPCInfo(NewNPCInfo);
			}
			GM->AddNewNPC(NPCData->GetNPCInfo());
		});
	}
	else
	{

	}
}

