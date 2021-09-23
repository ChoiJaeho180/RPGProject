// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include "GameFramework/Actor.h"
#include "RPGGameNPCData.generated.h"

UCLASS()
class RPGPROJECT_API ARPGGameNPCData : public AActor
{
	GENERATED_BODY()
private:
public:	
	// Sets default values for this actor's properties
	ARPGGameNPCData();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
