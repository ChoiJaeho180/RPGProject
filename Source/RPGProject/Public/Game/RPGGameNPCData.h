// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include "GameFramework/Actor.h"
#include "RPGGameNPCData.generated.h"

USTRUCT(BlueprintType)
struct FNPCInfo
{
	GENERATED_BODY()
	FVector Position;
	FString Village;
	FString Name;
	FString Type;
	TArray<FString> Speech;
	bool bQuest;
	UPROPERTY()
	USkeletalMesh* SkeletalMesh;
	TSubclassOf<UAnimInstance> AnimInstanceClass;
};

UCLASS()
class RPGPROJECT_API ARPGGameNPCData : public AActor
{
	GENERATED_BODY()
private:
	TArray<FNPCInfo> _NPCInfo;
public:	
	// Sets default values for this actor's properties
	ARPGGameNPCData();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	void SetNPCInfo(FNPCInfo NewInfo);
public:
	FORCEINLINE TArray<FNPCInfo> GetNPCInfo() { return _NPCInfo; }
};
