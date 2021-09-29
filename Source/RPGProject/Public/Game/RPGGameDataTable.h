// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include <Engine/DataTable.h>
#include "GameFramework/Actor.h"
#include "RPGGameDataTable.generated.h"


USTRUCT(BlueprintType)
struct FCharacterExp : public FTableRowBase
{
	GENERATED_BODY();
public:
	FCharacterExp() {};
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Data")
	int Level;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Data")
	int Exp;
};


UCLASS()
class RPGPROJECT_API ARPGGameDataTable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARPGGameDataTable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
