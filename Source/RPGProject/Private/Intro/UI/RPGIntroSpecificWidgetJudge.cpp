// Fill out your copyright notice in the Description page of Project Settings.
#include "Intro/UI/RPGIntroSpecificWidgetJudge.h"
#include "Intro/UI/RPGIntroBaseLayout.h"
#include "Containers/UnrealString.h"

FRPGIntroSpecificWidgetJudge::FRPGIntroSpecificWidgetJudge()
{
}

FRPGIntroSpecificWidgetJudge::~FRPGIntroSpecificWidgetJudge()
{
}

void FRPGIntroSpecificWidgetJudge::SetWidgetIdentifyMap(TMap<EIntroDerivedWidgetState, FString>& WidgetStatToIdentifyMap)
{
	_WidgetStatToIdentifyMap = WidgetStatToIdentifyMap;
}

FString FRPGIntroSpecificWidgetJudge::GetUpdateWidgetName(const EIntroDerivedWidgetState& UpdateWidgetState)
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

int FRPGIntroSpecificWidgetJudge::GetUpdateWidgetIndex(const TArray<URPGIntroBaseLayout*>& LayoutList, const EIntroDerivedWidgetState& UpdateWidgetState)
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
