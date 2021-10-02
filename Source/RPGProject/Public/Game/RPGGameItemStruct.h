// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include "Game/RPGGameEnumCollection.h"
#include "UObject/NoExportTypes.h"
#include "RPGGameItemStruct.generated.h"

class  UTexture2D;

USTRUCT(Blueprintable)
struct FRPGItemBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Item")
	EInventoryType InventoryType;
	UPROPERTY(EditAnywhere, Category = "Item")
	FName Name;
	UPROPERTY(EditAnywhere, Category = "Item")
	FText Description;
	UPROPERTY(EditAnywhere, Category = "Item")
	int Price;
};

USTRUCT(Blueprintable)
struct FRPGItemInfo : public FRPGItemBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Item")
	int Count;
};

USTRUCT(Blueprintable)
struct FRPGItemSlot : public FRPGItemBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Item")
	UTexture2D* Image;
};


/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameItemStruct : public UObject
{
	GENERATED_BODY()
	
};
