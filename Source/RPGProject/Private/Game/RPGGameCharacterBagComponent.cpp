// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/RPGGameCharacterBagComponent.h"
#include "Game/RPGGameDataTableManager.h"
#include "Common/RPGCommonGameInstance.h"

// Sets default values for this component's properties
URPGGameCharacterBagComponent::URPGGameCharacterBagComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	_Money = MakeShareable(new FMoney);
	_Money->Money = 10000;
	_Money->TimeStamp++;
	// ...
}

void URPGGameCharacterBagComponent::InitData(const TArray<FRPGRestItem>& RestItemData)
{
	URPGCommonGameInstance* GI = Cast<URPGCommonGameInstance>(GetWorld()->GetGameInstance());
	URPGGameDataTableManager* DTManager = GI->GetDataTableManager();
	for (int i = 0; i < RestItemData.Num(); i++)
	{
		TSharedPtr<FRPGItemInfo> NewItem = MakeShareable(new FRPGItemInfo);
		FGameItemType* ItemType = DTManager->GetNameToData(RestItemData[i].Name);
		NewItem->Name = RestItemData[i].Name;
		NewItem->Price = ItemType->Price;
		NewItem->InventoryType = ItemType->InventoryType;
		NewItem->Description = ItemType->Description;
		NewItem->Count = RestItemData[i].Count;
		AddItem(NewItem);
	}
}


// Called when the game starts
void URPGGameCharacterBagComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void URPGGameCharacterBagComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void URPGGameCharacterBagComponent::UpdateMoney(int AddMoney)
{
	_Money->Money += AddMoney;
	_Money->TimeStamp++;
}

void URPGGameCharacterBagComponent::AddItem(const TSharedPtr<FRPGItemInfo>& NewItem)
{
	TSharedPtr<FRPGItemInfo> ExistItem = FindItem(NewItem->Name);
	if (ExistItem != nullptr)
	{
		ExistItem->Count += NewItem->Count;
		ExistItem->TimeStamp++;
		return;
	}
	_CharacterItems.Add(NewItem);
	
}

void URPGGameCharacterBagComponent::RemoveItem(const TSharedPtr<FRPGItemInfo>& NewItem)
{
	TSharedPtr<FRPGItemInfo> ExistItem = FindItem(NewItem->Name);
	if (ExistItem == nullptr)
		return;

	if(ExistItem->Count > NewItem->Count)
	{
		ExistItem->Count -= NewItem->Count;
	}
	else
	{
		_CharacterItems.Remove(ExistItem);
	}
	ExistItem->TimeStamp++;
}

bool URPGGameCharacterBagComponent::RemoveItem(FName Name, int Count)
{
	TSharedPtr<FRPGItemInfo> ExistItem = FindItem(Name);
	if (ExistItem == nullptr)
		return false;
	if (ExistItem->Count > Count)
	{
		ExistItem->Count -= Count;
	}
	else
	{
		_CharacterItems.Remove(ExistItem);
	}
	ExistItem->TimeStamp++;
	return true;
}

TSharedPtr<FRPGItemInfo> URPGGameCharacterBagComponent::FindItem(FName Name)
{
	for (int i = 0; i < _CharacterItems.Num(); i++)
	{
		if (_CharacterItems[i]->Name == Name)
		{
			return _CharacterItems[i];
		}
	}
	return nullptr;
}

