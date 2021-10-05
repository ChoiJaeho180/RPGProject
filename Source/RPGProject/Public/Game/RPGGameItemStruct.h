// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include "Game/RPGGameEnumCollection.h"
#include "UObject/NoExportTypes.h"
#include "RPGGameItemStruct.generated.h"

class  UTexture2D;

USTRUCT(Blueprintable)
struct FRPGRestItem
{
	GENERATED_USTRUCT_BODY()
public:
	FName Name;
	int Count;
	int SlotIndex;
};
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
	int Count =0;
	int TimeStamp =0;
	void SetInfo(int NewCount = 0, int NewPrice =0, FText NewDescription = FText(), FName NewName =FName(), EInventoryType NewType = EInventoryType::ETC_INVENTORY,int NewTimeStamp =1)
	{
		Count = NewCount;
		Price = NewPrice;
		Description = NewDescription;
		Name = NewName;
		InventoryType = NewType;
		TimeStamp = NewTimeStamp;
	}
	void SetInfo(const TSharedPtr<FRPGItemInfo>& NewInfo)
	{
		Count = NewInfo->Count;
		Price = NewInfo->Price;
		Description = NewInfo->Description;
		Name = NewInfo->Name;
		InventoryType =NewInfo->InventoryType;
		TimeStamp = NewInfo->TimeStamp;
	}
};

USTRUCT(Blueprintable)
struct FRPGItemSlot : public FRPGItemInfo
{
	GENERATED_USTRUCT_BODY()
public:
	int SlotIndex;
	UPROPERTY(EditAnywhere, Category = "Item")
	UTexture2D* Image = nullptr;
	void SetInfo(UTexture2D* NewImage, int NewSlotIndex)
	{
		Image = NewImage;
		SlotIndex = NewSlotIndex;
	}
	void SetInfo(const TSharedPtr<FRPGItemInfo>& NewInfo)
	{
		FRPGItemInfo::SetInfo(NewInfo);
	}
	void SetInfo(int NewCount = 0, int NewPrice = 0, FText NewDescription = FText(), FName NewName = FName(), EInventoryType NewType = EInventoryType::ETC_INVENTORY, int NewTimeStamp = 1)
	{
		Count = NewCount;
		Price = NewPrice;
		Description = NewDescription;
		Name = NewName;
		InventoryType = NewType;
		TimeStamp = NewTimeStamp;
	}
};



/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameItemStruct : public UObject
{
	GENERATED_BODY()
	
};
