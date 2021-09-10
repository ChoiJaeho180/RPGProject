// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/REST/RPGCommonRestExecutorElements.h"
#include "Common/REST/RPGCommonBaseExecutor.h"

// Sets default values
ARPGCommonRestExecutorElements::ARPGCommonRestExecutorElements()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RestApiLoginExecutorClass = ARPGCommonRestLoginExecutor::StaticClass();
	RestApiNewCharacterExecutorClass = ARPGCommonNewCharacterExecutor::StaticClass();
}

// Called when the game starts or when spawned
void ARPGCommonRestExecutorElements::BeginPlay()
{
	Super::BeginPlay();
	_RestApiExecutors.Add(GetWorld()->SpawnActor<ARPGCommonRestLoginExecutor>(RestApiLoginExecutorClass));
	_RestApiExecutors.Add(GetWorld()->SpawnActor<ARPGCommonNewCharacterExecutor>(RestApiNewCharacterExecutorClass));
}

void ARPGCommonRestExecutorElements::Update(TSharedPtr<FJsonObject>& JsonObject)
{
	FString Type = JsonObject->GetStringField("MsgType");
	for (int i = 0; i < _RestApiExecutors.Num(); i++)
	{
		if (Type != _RestApiExecutors[i]->GetRestIdentify())
			continue;

		_RestApiExecutors[i]->Update(JsonObject);
		break;
	}

}

