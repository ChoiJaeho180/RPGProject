// Fill out your copyright notice in the Description page of Project Settings.
#include "Common/REST/RPGCommonQuestInfoExecutor.h"
#include "Game/RPGGameQuestManager.h"
#include "Game/RPGGameGameMode.h"
#include "Common/RPGCommonGameInstance.h"

// Sets default values
ARPGCommonQuestInfoExecutor::ARPGCommonQuestInfoExecutor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	_RestMsgIdentify = FString("QUESTINFO");
}

// Called when the game starts or when spawned
void ARPGCommonQuestInfoExecutor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARPGCommonQuestInfoExecutor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARPGCommonQuestInfoExecutor::Update(TSharedPtr<FJsonObject>& RestMsg)
{
	auto Field = RestMsg->TryGetField("ResultCode");
	if (Field == nullptr) return;

	auto PreviousQuest = RestMsg->TryGetField("Previouslist");
	if (PreviousQuest == nullptr) return;
	auto PreviousQuestList = PreviousQuest->AsArray();
	TArray<FRPGQuestInfo> NewPreviousQuestList;
	for (int i = 0; i < PreviousQuestList.Num(); i++)
	{
		auto PositionInfo = PreviousQuestList[i]->AsObject();
		FString NpcName = PositionInfo->TryGetField("NpcName")->AsString();
		FString Speech = PositionInfo->TryGetField("Speech")->AsString();
		int MinLevel = FCString::Atoi(*PositionInfo->TryGetField("MinLevel")->AsString());
		int QuestNumber = FCString::Atoi(*PositionInfo->TryGetField("QuestNumber")->AsString());
		FRPGQuestInfo NewInfo;
		NewInfo.SetInfo(NpcName, Speech, QuestNumber, MinLevel);
		NewPreviousQuestList.Add(NewInfo);
	}
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		ARPGGameGameMode* GM = Cast<ARPGGameGameMode>(GetWorld()->GetAuthGameMode());
		URPGCommonGameInstance* GameInstance = Cast<URPGCommonGameInstance>(GetGameInstance());
		GM->SetQuestInfo(NewPreviousQuestList);

		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
		GameInstance->PostRequest("/game/getnpcinfo", JsonObject);
	});
	
}

