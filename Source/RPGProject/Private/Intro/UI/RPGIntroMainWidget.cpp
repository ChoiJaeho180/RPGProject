// Fill out your copyright notice in the Description page of Project Settings.
#include "Intro/UI/RPGIntroMainWidget.h"
#include "Intro/RPGIntroController.h"
#include "Intro/UI/RPGIntroBaseLayout.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Image.h"

void URPGIntroMainWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetLayoutList();

	TMap<EIntroDerivedWidgetState, FString> WidgetStatToIdentifyMap;
	WidgetStatToIdentifyMap.Add(EIntroDerivedWidgetState::MAIN_LOGIN, FString("WB_Login_Layout"));
	WidgetStatToIdentifyMap.Add(EIntroDerivedWidgetState::MAIN_TITLE, FString("WB_Title_Layout"));
	WidgetStatToIdentifyMap.Add(EIntroDerivedWidgetState::MAIN_REGISTER, FString("WB_Register_Layout"));
	_RPGIntroSpecificWidgetJudge.SetWidgetIdentifyMap(WidgetStatToIdentifyMap);
}

void URPGIntroMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	_FadeInImage = Cast<UImage>(GetWidgetFromName(TEXT("FadeInImage")));
	SetFadeInAnimation();
	int LayoutIndex = _RPGIntroSpecificWidgetJudge.GetUpdateWidgetIndex(_IntroLayoutList, EIntroDerivedWidgetState::MAIN_LOGIN);
	if (LayoutIndex == -1)
		return;
	_IntroLayoutList[LayoutIndex]->delegateSendWidgetChange.BindUObject(this, &URPGIntroMainWidget::OnPreWidgetChange);
}

void URPGIntroMainWidget::SetFadeInAnimation()
{
	_FadeInAnimation = GetAnimation(FString("FadeIn_INST"));
	delegateEndedFadeIn.BindDynamic(this, &URPGIntroMainWidget::OnEndedFadeInAnim);
	BindToAnimationFinished(_FadeInAnimation, delegateEndedFadeIn);
}

void URPGIntroMainWidget::OnPreWidgetChange(const EIntroDerivedWidgetState& NewState, const int& ZOrder)
{
	UE_LOG(LogTemp, Warning, TEXT("dwdwdwd"));
	_FadeInImage->SetVisibility(ESlateVisibility::Visible);
	PlayAnimation(_FadeInAnimation);
}

void URPGIntroMainWidget::OnEndedFadeInAnim()
{
	ChangeLayoutAndWidget(EIntroDerivedWidgetState::TO_LOBBY, 5);
	_FadeInImage->SetVisibility(ESlateVisibility::Hidden);
	UE_LOG(LogTemp, Warning, TEXT("called OnEndedFadeInAnim"));
}



