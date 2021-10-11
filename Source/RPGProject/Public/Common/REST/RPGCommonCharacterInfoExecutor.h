// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/REST/RPGCommonBaseExecutor.h"
#include "GameFramework/Actor.h"
#include "RPGCommonCharacterInfoExecutor.generated.h"

USTRUCT(BlueprintType)
struct FCharacterInfo
{
	GENERATED_BODY()
	TMap<FString, FString> Stat;
	TMap<FString, FString> Items;
	FVector CurrentPosition;
	FString CurrentVillage;
	FString Job;
	int Level;
};
/**
 *
 */
UCLASS()
class RPGPROJECT_API ARPGCommonCharacterInfoExecutor : public ARPGCommonBaseExecutor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARPGCommonCharacterInfoExecutor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual void Update(TSharedPtr<FJsonObject>& RestMsg) override;
};
