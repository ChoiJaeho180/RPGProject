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

	// ...
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

void URPGGameCharacterBagComponent::TestInfo()
{
	
	URPGCommonGameInstance* GI = Cast<URPGCommonGameInstance>(GetWorld()->GetGameInstance());
	URPGGameDataTableManager* DTManager = GI->GetDataTableManager();
	auto Test = DTManager->GetData();
	TSharedPtr<FRPGItemInfo> NewData = MakeShareable(new FRPGItemInfo());
	NewData->SetInfo(5, Test[0]->Price, Test[0]->Description, Test[0]->Name, Test[0]->InventoryType);
	_CharacterItems.Add((NewData));
	
}

void URPGGameCharacterBagComponent::AddItem(const TSharedPtr<FRPGItemInfo>& NewItem)
{
	TSharedPtr<FRPGItemInfo> ExistItem = FindItem(NewItem);
	if (ExistItem != nullptr)
	{
		ExistItem->Count += NewItem->Count;
		return;
	}
	_CharacterItems.Add(ExistItem);
}

void URPGGameCharacterBagComponent::RemoveItem(const TSharedPtr<FRPGItemInfo>& NewItem)
{
	TSharedPtr<FRPGItemInfo> ExistItem = FindItem(NewItem);
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
}

TSharedPtr<FRPGItemInfo> URPGGameCharacterBagComponent::FindItem(const TSharedPtr<FRPGItemInfo>& NewItem)
{
	for (int i = 0; i < _CharacterItems.Num(); i++)
	{
		if (_CharacterItems[i]->Name == NewItem->Name)
		{
			return _CharacterItems[i];
		}
	}
	return nullptr;
}

