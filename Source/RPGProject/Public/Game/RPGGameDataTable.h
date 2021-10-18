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
struct FPortalInfo : public FTableRowBase
{
	GENERATED_BODY();
public:
	FPortalInfo() {};
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Data")
	FVector CurrentPosition;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Data")
	FString CurrentMap;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Data")
	FString NextMap;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Data")
	FVector NextPosition;
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

USTRUCT(BlueprintType)
struct FGameSkillType : public FTableRowBase
{
	GENERATED_BODY();
public:
	FGameSkillType() {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FText Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UTexture2D* Image;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float _Coefficient;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float _CoolDown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int _MP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float _AttackRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float _AttackLocation;
};


USTRUCT(BlueprintType)
struct FGameEnemyInfo : public FTableRowBase
{
	GENERATED_BODY();
public:
	FGameEnemyInfo() {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	EEnemyType EnemyType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	int Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	int HP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	int Exp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	int AverageDropGold;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	TArray<int> BaseAttack;

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
