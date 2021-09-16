// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include "Dom/JsonObject.h"
#include "Engine/GameInstance.h"
#include "RPGCommonGameInstance.generated.h"

class ARPGCommonRestManager;

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGCommonGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	ARPGCommonRestManager* _RestManager;
	FString _CurrentCharacterName;
	FString _TempToken;
public:
	URPGCommonGameInstance();
	virtual void Init() override;
	bool PostRequest(FString URL, TSharedPtr<FJsonObject>& JsonObject);

	void Release();

public:
	FORCEINLINE void SetCharacterName(FString NewName) { _CurrentCharacterName = NewName; }
public:
	TSubclassOf<ARPGCommonRestManager> RestManagerClass;
	USkeletalMesh* CharacterSkeletalMeshObject;
};
