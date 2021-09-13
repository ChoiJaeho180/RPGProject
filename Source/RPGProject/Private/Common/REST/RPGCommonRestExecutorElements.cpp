// Fill out your copyright notice in the Description page of Project Settings.
#include "Common/REST/RPGCommonRestExecutorElements.h"
#include "Common/REST/RPGCommonBaseExecutor.h"
#include "Common/REST/RPGCommonSetToken.h"

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
	ARPGCommonRestLoginExecutor* LoginExecutor = GetWorld()->SpawnActor<ARPGCommonRestLoginExecutor>(RestApiLoginExecutorClass);
	IRPGCommonSetToken* temp = 	Cast<IRPGCommonSetToken>(LoginExecutor);
	temp->delgateSetToken.BindUObject(this, &ARPGCommonRestExecutorElements::SetToken);
	_RestApiExecutors.Add(LoginExecutor);
	_RestApiExecutors.Add(GetWorld()->SpawnActor<ARPGCommonNewCharacterExecutor>(RestApiNewCharacterExecutorClass));
}

void ARPGCommonRestExecutorElements::SetToken(const FString& Token)
{
	delegateSetToken.ExecuteIfBound(Token);
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

