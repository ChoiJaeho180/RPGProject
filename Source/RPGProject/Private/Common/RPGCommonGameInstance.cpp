// Fill out your copyright notice in the Description page of Project Settings.
#include "Common/RPGCommonGameInstance.h"
#include "Common/REST/RPGCommonRestManager.h"
#include "Game/RPGGameNPCData.h"
#include "Game/RPGGameDataCopy.h"

URPGCommonGameInstance::URPGCommonGameInstance()
{
	RestManagerClass = ARPGCommonRestManager::StaticClass();
	RPGGameClass = ARPGGameNPCData::StaticClass();
	GameDataCopyClass = ARPGGameDataCopy::StaticClass();

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_WARRIOR(TEXT("SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Meshes/Greystone.Greystone'"));
	if (SK_WARRIOR.Succeeded())
	{
		CharacterSkeletalMeshObject = SK_WARRIOR.Object;
	}
}

void URPGCommonGameInstance::Init()
{
	if (_RestManager != nullptr)
	{
		GetWorld()->DestroyActor(_RestManager);
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
