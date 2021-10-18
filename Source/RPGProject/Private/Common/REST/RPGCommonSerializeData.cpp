// Fill out your copyright notice in the Description page of Project Settings.
#include "Common/REST/RPGCommonSerializeData.h"

FString URPGCommonSerializeData::GetCharacterStat(TMap<FString, int> CharacterStat)
{
	FString Serialize;
	for (auto& Elem : CharacterStat)
	{
		Serialize +=Elem.Key + ":" + FString::FromInt(Elem.Value) + ",";
	}
	if (Serialize.Len() != 0)
	{
		Serialize[Serialize.Len() - 1] = '\0';
	}

	return Serialize;
}

FString URPGCommonSerializeData::GetMoney(int Money)
{
	return "Money:" + FString::FromInt(Money);
}

FString URPGCommonSerializeData::GetLastPosition(const FString & Village, const FVector & Position)
{
	FString Serialize;
	Serialize = "Map:" + Village + ",";
	Serialize += "X:" + FString::FromInt(Position.X) + ",";
	Serialize += "Y:" + FString::FromInt(Position.Y) + ",";
	Serialize += "Z:" + FString::FromInt(Position.Z + 100);
	return Serialize;
}
FString URPGCommonSerializeData::GetItemsData(const TArray<TSharedPtr<FRPGItemSlot>>& ItemsData)
{
	FString Serialize;
	
	for (int i = 0; i < ItemsData.Num(); i++)
	{
		if (ItemsData[i]->Image == nullptr)
			continue;
		Serialize += ItemsData[i]->Name.ToString() + ":";
		Serialize += FString::FromInt(ItemsData[i]->SlotIndex) + "-";
		Serialize += FString::FromInt(ItemsData[i]->Count) + ",";
	}
	if (Serialize.Len() != 0)
	{
		Serialize[Serialize.Len() - 1] = '\0';
	}
	return Serialize;
}