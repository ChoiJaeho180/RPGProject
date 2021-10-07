// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include <Engine/DataTable.h>
#include "GameFramework/Actor.h"
#include "RPGGameDataTable.generated.h"

class UTexture2D;

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

USTRUCT(BlueprintType)
struct FGameItemType : public FTableRowBase
{
	GENERATED_BODY();
public:
	FGameItemType() {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	EInventoryType InventoryType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FText Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UTexture2D* Image;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int Price;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TArray<FString> Property;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TArray<int> Stat;
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
