// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameSpecificWidgetJudge.h"
#include "Game/UI/RPGGameBaseLayout.h"

FRPGGameSpecificWidgetJudge::FRPGGameSpecificWidgetJudge()
{
}

FRPGGameSpecificWidgetJudge::~FRPGGameSpecificWidgetJudge()
{
}

void FRPGGameSpecificWidgetJudge::SetWidgetIdentifyMap(TMap<EGameMainUIType, FString>& WidgetStatToIdentifyMap)
{
	_WidgetStatToIdentifyMap = WidgetStatToIdentifyMap;
}

int FRPGGameSpecificWidgetJudge::GetUpdateWidgetIndex(const TArray<URPGGameBaseLayout*>& LayoutList, const EGameMainUIType& UpdateWidgetState)
{
	int UpdateLayoutIndex = -1;
	FString result = GetUpdateWidgetName(UpdateWidgetState);
	for (int i = 0; i < LayoutList.Num(); i++)
	{
		FString LayoutName = LayoutList[i]->GetName();
		if (result == LayoutName)
		{
			UpdateLayoutIndex = i;
			break;
		}
	}
	return UpdateLayoutIndex;
}

FString FRPGGameSpecificWidgetJudge::GetUpdateWidgetName(const EGameMainUIType& UpdateWidgetState)
{
	FString UpdateWidgetName = "";
	for (auto& item : _WidgetStatToIdentifyMap)
	{
		if (item.Key != UpdateWidgetState)
			continue;
		UpdateWidgetName = item.Value;
		break;
	}
	return UpdateWidgetName;
}
