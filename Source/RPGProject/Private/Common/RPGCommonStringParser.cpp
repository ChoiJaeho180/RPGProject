// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/RPGCommonStringParser.h"

RPGCommonStringParser::RPGCommonStringParser()
{
}

RPGCommonStringParser::~RPGCommonStringParser()
{
}

TMap<FString, FString> RPGCommonStringParser::StringParsing(const FString& Data)
{
	TMap<FString, FString> NewData;
	TArray<FString> TempArray;
	Data.ParseIntoArray(TempArray, TEXT(","), true);
	for (int i = 0; i < TempArray.Num(); i++)
	{
		FString Key, Value;
		TempArray[i].Split(TEXT(":"), &Key, &Value);
		NewData.Add(Key, Value);
	}
	return NewData;
}
TArray<FString> RPGCommonStringParser::CommaStringParsing(const FString& Data)
{
	TArray<FString> NewData;
	Data.ParseIntoArray(NewData, TEXT(","), true);
	return NewData;
}

TArray<FRPGRestItem> RPGCommonStringParser::ItemsDataParsing(const FString& Data)
{
	TArray<FRPGRestItem> NewData;
	TArray<FString> TempArray;
	Data.ParseIntoArray(TempArray, TEXT(","), true);
	for (int i = 0; i < TempArray.Num(); i++)
	{
		FRPGRestItem New;
		FString ItemName, Value;
		TempArray[i].Split(TEXT(":"), &ItemName, &Value);
		
		FString Slot, Count;
		Value.Split(TEXT("-"), &Slot, &Count);

		New.Name = FName(*ItemName);
		New.Count = FCString::Atoi(*Count);
		New.SlotIndex = FCString::Atoi(*Slot);
		NewData.Add(New);
	}
	return NewData;
}
