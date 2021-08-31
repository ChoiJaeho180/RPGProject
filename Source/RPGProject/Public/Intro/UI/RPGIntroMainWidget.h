// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Intro/UI/RPGIntroSpecificWidgetJudge.h"
#include "Blueprint/UserWidget.h"
#include "RPGIntroMainWidget.generated.h"

class UWidgetSwitcher;
class URPGIntroBaseLayout;

UCLASS()
class RPGPROJECT_API URPGIntroMainWidget : public UUserWidget
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
	void ChangeLayout(const EIntroUIWidgetState& NewState, const int& ZOrder);
public:
	void NativePreConstruct() override;
	void NativeConstruct() override;
protected:
};
