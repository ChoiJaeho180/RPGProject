// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../RPGProject.h"
#include "Game/RPGGameEnumCollection.h"
#include "UObject/NoExportTypes.h"
#include "RPGGameItemStruct.generated.h"

class  UTexture2D;

USTRUCT(Blueprintable)
struct FMoney
{
	GENERATED_USTRUCT_BODY()
public:
	int Money = 0;
	int TimeStamp = 0;
};

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
	int Price = 0;
	
};

USTRUCT(Blueprintable)
struct FRPGItemInfo : public FRPGItemBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Item")
	int Count =-1;
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
	void SetInfo(int NewCount, int NewTimeStamp)
	{
		Count = NewCount;
		TimeStamp = NewTimeStamp;
	}
	void SetInfo(const TSharedPtr<FRPGItemInfo>& NewInfo)
	{
		Count = NewInfo->Count;
		Price = NewInfo->Price;
		Description = NewInfo->Description;
		Name = NewInfo->Name;
		TimeStamp = NewInfo->TimeStamp;
	}
};

USTRUCT(Blueprintable)
struct FRPGItemSlot : public FRPGItemInfo
{
	GENERATED_USTRUCT_BODY()
public:
	int SlotIndex = -1;
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
	void SetInfoT(const TSharedPtr<FRPGItemInfo>& NewInfo)
	{
		Count = NewInfo->Count;
		TimeStamp = NewInfo->TimeStamp;
	}
	void SetEmpty()
	{
		Image = nullptr;
		SlotIndex = -1;
		Count = -1;
		TimeStamp = 0;
		InventoryType = EInventoryType::ETC_INVENTORY;
		Name = FName("");
		Description = FText::FromString("");
		Price = 0;
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

USTRUCT(BlueprintType)
struct FGameSkillDataCopyInfo
{
	GENERATED_BODY();
public:
	FGameSkillDataCopyInfo() {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float CurrentCoolDown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float CoolDown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString Identify;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	ESkillState SkillState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int TimeStamp;
};


/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameItemStruct : public UObject
{
	GENERATED_BODY()
	
};
