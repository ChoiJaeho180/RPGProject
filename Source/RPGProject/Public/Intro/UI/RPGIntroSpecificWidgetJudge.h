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
	TMap<EIntroUIWidgetState, FString> _WidgetStatToIdentifyMap;
private:
	FString GetUpdateWidgetName(const EIntroUIWidgetState& UpdateWidgetState);
public:
	FRPGIntroSpecificWidgetJudge();
	~FRPGIntroSpecificWidgetJudge();
	int GetUpdateWidgetIndex(const TArray<URPGIntroBaseLayout*>& LayoutList , const EIntroUIWidgetState& UpdateWidgetState);

};
