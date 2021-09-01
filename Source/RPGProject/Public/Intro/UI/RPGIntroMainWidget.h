// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Intro/UI/RPGIntroSpecificWidgetJudge.h"
#include "Intro/UI/RPGIntroBaseWidget.h"
#include "RPGIntroMainWidget.generated.h"

class UWidgetSwitcher;
class URPGIntroBaseLayout;

UCLASS()
class RPGPROJECT_API URPGIntroMainWidget : public URPGIntroBaseWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* IntroMainSwicher;
	FRPGIntroSpecificWidgetJudge _RPGIntroSpecificWidgetJudge;
	UPROPERTY()
	TArray<URPGIntroBaseLayout*> _IntroLayoutList;
private:
	void SetLayoutList();
	void ChangeLayout(const EIntroDerivedWidgetState& NewState, const int& ZOrder);
public:
	void NativePreConstruct() override;
	void NativeConstruct() override;
protected:
};
