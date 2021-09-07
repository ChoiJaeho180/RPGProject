// Fill out your copyright notice in the Description page of Project Settings.
#include "Common/RPGCommonGameInstance.h"
#include "Common/REST/RPGCommonRestManager.h"

URPGCommonGameInstance::URPGCommonGameInstance()
{
	RestManagerClass = ARPGCommonRestManager::StaticClass();
}

void URPGCommonGameInstance::Init()
{
	_RestManager = GetWorld()->SpawnActor<ARPGCommonRestManager>(RestManagerClass);
}

bool URPGCommonGameInstance::PostRequest(FString URL, TSharedPtr<FJsonObject> JsonObject)
{
	_RestManager->PostRequest(URL, JsonObject);
	return false;
}

void URPGCommonGameInstance::Release()
{
	_RestManager->Release();
}
