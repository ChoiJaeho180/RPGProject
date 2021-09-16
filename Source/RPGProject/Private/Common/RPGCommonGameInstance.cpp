// Fill out your copyright notice in the Description page of Project Settings.
#include "Common/RPGCommonGameInstance.h"
#include "Common/REST/RPGCommonRestManager.h"

URPGCommonGameInstance::URPGCommonGameInstance()
{
	RestManagerClass = ARPGCommonRestManager::StaticClass();
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
}

bool URPGCommonGameInstance::PostRequest(FString URL, TSharedPtr<FJsonObject>& JsonObject)
{
	_RestManager->PostRequest(URL, JsonObject);
	return false;
}

void URPGCommonGameInstance::Release()
{
	_RestManager->Release();
}
