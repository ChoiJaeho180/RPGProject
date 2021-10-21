// Fill out your copyright notice in the Description page of Project Settings.
#include "Common/REST/RPGCommonNewAccountExecutor.h"
#include "Intro/RPGIntroController.h"
#include "Intro/UI/RPGIntroUIManager.h"
#include "Common/UI/RPGCommonChangeScene.h"
#include "Intro/UI/RPGIntroBaseWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Intro/UI/RPGIntroCreateCharacterLayout.h"
#include "Intro/UI/RPGIntroInputCharacterInfoLayout.h"
#include "Intro/UI/RPGIntroLobbySlotInfo.h"
#include "Common/REST/RPGGameSendRegiterResult.h"
#include "Intro/UI/RPGIntroRegisterLayout.h"

ARPGCommonNewAccountExecutor::ARPGCommonNewAccountExecutor()
{
	_RestMsgIdentify = FString("NEWACCOUNT");

}
void ARPGCommonNewAccountExecutor::BeginPlay()
{
	Super::BeginPlay();
}

void ARPGCommonNewAccountExecutor::Update(TSharedPtr<FJsonObject>& RestMsg)
{
	auto Field = RestMsg->TryGetField("ResultCode");
	if (Field == nullptr) return;
	
	auto ResultCode = RestMsg->TryGetField("Result")->AsString();
	ARPGIntroController* CurrentController = Cast<ARPGIntroController>(GetWorld()->GetFirstPlayerController());
	URPGIntroBaseWidget* CurrentWidget = CurrentController->GetUIManager()->GetCurrentWidget();
	URPGIntroRegisterLayout* CurrentLayout = Cast<URPGIntroRegisterLayout>(CurrentWidget->GetIntroSwitcher()->GetActiveWidget());
	IRPGGameSendRegiterResult* Send = Cast<IRPGGameSendRegiterResult>(CurrentWidget);
	CurrentLayout->SetRestResult(ResultCode);
}
