// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RPGGameMapInfo.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGGameMapInfo : public UObject
{
	GENERATED_BODY()
private:
	FString _MapName;
public:
	FORCEINLINE void SetMapName(const FString& MapName) { _MapName = MapName; }
	FORCEINLINE FString GetMapName() { return _MapName; }
};
