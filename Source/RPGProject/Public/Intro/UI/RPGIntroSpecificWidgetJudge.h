// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"

class URPGIntroBaseLayout;
/**
 * 
 */
class RPGPROJECT_API FRPGIntroSpecificWidgetJudge
{
private:
	TMap<EIntroDerivedWidgetState, FString> _WidgetStatToIdentifyMap;
private:
	FString GetUpdateWidgetName(const EIntroDerivedWidgetState& UpdateWidgetState);
public:
	FRPGIntroSpecificWidgetJudge();
	~FRPGIntroSpecificWidgetJudge();
	void SetWidgetIdentifyMap(TMap<EIntroDerivedWidgetState, FString>& WidgetStatToIdentifyMap);
	int GetUpdateWidgetIndex(const TArray<URPGIntroBaseLayout*>& LayoutList , const EIntroDerivedWidgetState& UpdateWidgetState);

};
