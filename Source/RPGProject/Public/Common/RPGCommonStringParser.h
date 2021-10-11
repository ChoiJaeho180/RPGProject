// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/RPGGameItemStruct.h"

/**
 * 
 */
class RPGPROJECT_API RPGCommonStringParser
{
public:
	RPGCommonStringParser();
	~RPGCommonStringParser();
	static FString GetSpecificStat(const FString& Data, const FString& StatName);
	static TMap<FString, FString> SingleStringParsing(const FString& Data);
	static TMap<FString, FString> StringParsing(const FString& Data);
	static TArray<FString> CommaStringParsing(const FString& Data);
	static TArray<FRPGRestItem> ItemsDataParsing(const TArray<FString>& TempArray);
};
