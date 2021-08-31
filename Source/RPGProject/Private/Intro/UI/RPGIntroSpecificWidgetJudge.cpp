// Fill out your copyright notice in the Description page of Project Settings.
#include "Intro/UI/RPGIntroSpecificWidgetJudge.h"
#include "Intro/UI/RPGIntroBaseLayout.h"
#include "Containers/UnrealString.h"

FRPGIntroSpecificWidgetJudge::FRPGIntroSpecificWidgetJudge()
{
	_WidgetStatToIdentifyMap.Add(EIntroUIWidgetState::Login, FString("WB_Login_Layout"));
	_WidgetStatToIdentifyMap.Add(EIntroUIWidgetState::Title, FString("WB_Title_Layout"));
	_WidgetStatToIdentifyMap.Add(EIntroUIWidgetState::Register, FString("WB_Register_Layout"));
}

FRPGIntroSpecificWidgetJudge::~FRPGIntroSpecificWidgetJudge()
{
}

FString FRPGIntroSpecificWidgetJudge::GetUpdateWidgetName(const EIntroUIWidgetState& UpdateWidgetState)
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

int FRPGIntroSpecificWidgetJudge::GetUpdateWidgetIndex(const TArray<URPGIntroBaseLayout*>& LayoutList, const EIntroUIWidgetState& UpdateWidgetState)
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
