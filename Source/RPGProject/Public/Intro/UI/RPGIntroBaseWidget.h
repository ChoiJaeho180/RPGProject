// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Intro/UI/RPGIntroSpecificWidgetJudge.h"
#include "Blueprint/UserWidget.h"
#include "RPGIntroBaseWidget.generated.h"

class UWidgetSwitcher;
class URPGIntroBaseLayout;
class UWidgetAnimation;

DECLARE_DELEGATE_OneParam(FChangeWidgetDelegate, const EIntroUIWidgetState&);
/**
 * 
 */
UCLASS()
class RPGPROJECT_API URPGIntroBaseWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* IntroSwicher;

	UPROPERTY()
	TArray<URPGIntroBaseLayout*> _IntroLayoutList;
	FRPGIntroSpecificWidgetJudge _RPGIntroSpecificWidgetJudge;
public:
	void ChangeLayout(const EIntroDerivedWidgetState& NewState, const int& ZOrder=0);
	void ChangeWidget(const EIntroUIWidgetState& NewState, const int& ZOrder = 0);
	void SetLayoutList();
	virtual UWidgetSwitcher* GetIntroSwitcher() const;
public:
	FChangeWidgetDelegate delegateChangeUI;
};
