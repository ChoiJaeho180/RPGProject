// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"

class URPGGameBaseLayout;
/**
 * 
 */
class RPGPROJECT_API FRPGGameSpecificWidgetJudge
{
private:
	TMap<EGameMainUIType, FString> _WidgetStatToIdentifyMap;

public:
	FRPGGameSpecificWidgetJudge();
	~FRPGGameSpecificWidgetJudge();
	void SetWidgetIdentifyMap(TMap<EGameMainUIType, FString>& WidgetStatToIdentifyMap);
	int GetUpdateWidgetIndex(const TArray<URPGGameBaseLayout*>& LayoutList, const EGameMainUIType& UpdateWidgetState);

private:
	FString GetUpdateWidgetName(const EGameMainUIType& UpdateWidgetState);


};
