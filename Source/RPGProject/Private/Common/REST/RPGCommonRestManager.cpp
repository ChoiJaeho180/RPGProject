// Fill out your copyright notice in the Description page of Project Settings.

#include "Common/REST/RPGCommonRestManager.h"
#include "Common/REST/RPGCommonRestRequestor.h"
#include "Common/REST/RPGCommonBaseExecutor.h"
#include "Common/REST/RPGCommonRestExecutorElements.h"

// Sets default values
ARPGCommonRestManager::ARPGCommonRestManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RestApiRequestorClass = ARPGCommonRestRequestor::StaticClass();
	RestApiElementsClass = ARPGCommonRestExecutorElements::StaticClass();
}

// Called when the game starts or when spawned
void ARPGCommonRestManager::BeginPlay()
{
	Super::BeginPlay();
	_RestApiRequestor = GetWorld()->SpawnActor<ARPGCommonRestRequestor>(RestApiRequestorClass);
	_RestApiRequestor->delegateRestApiResponse.BindUObject(this, &ARPGCommonRestManager::PushQueue);

	_RestExecutorElements = GetWorld()->SpawnActor<ARPGCommonRestExecutorElements>(RestApiElementsClass);
	Update();
}

void ARPGCommonRestManager::BeginDestroy()
{
	Super::BeginDestroy();
}

// Called every frame
void ARPGCommonRestManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARPGCommonRestManager::Update()
{
	AsyncTask(ENamedThreads::AnyThread, [=]()
	{
		while(_bEndedGame == false)
		{
			if (_RestApiMsg.IsEmpty() != true)
			{
				TSharedPtr<FJsonObject> RestMsg;
				_RestApiMsg.Dequeue(RestMsg);
				_RestExecutorElements->Update(RestMsg);
			}
			FPlatformProcess::Sleep(0.1f);
		}
	});
}

bool ARPGCommonRestManager::PostRequest(FString URL, TSharedPtr<FJsonObject>& JsonObject)
{
	_RestApiRequestor->HttpCall(URL, JsonObject);
	return false;
}

void ARPGCommonRestManager::PushQueue(TSharedPtr<FJsonObject>& JsonObject)
{
	_RestApiMsg.Enqueue(JsonObject);
}

void ARPGCommonRestManager::Release()
{
	_bEndedGame = true;
	FPlatformProcess::Sleep(0.3f);
}


