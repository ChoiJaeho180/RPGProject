// Fill out your copyright notice in the Description page of Project Settings.
#include "Common/REST/RPGCommonNewCharacterExecutor.h"
#include "Intro/RPGIntroController.h"
#include "Intro/UI/RPGIntroUIManager.h"
#include "Common/UI/RPGCommonChangeScene.h"
#include "Intro/UI/RPGIntroBaseWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Intro/UI/RPGIntroCreateCharacterLayout.h"
#include "Intro/UI/RPGIntroInputCharacterInfoLayout.h"
#include "Intro/UI/RPGIntroLobbySlotInfo.h"

ARPGCommonNewCharacterExecutor::ARPGCommonNewCharacterExecutor()
{
	_RestMsgIdentify = FString("NEWCHARACTER");
}

void ARPGCommonNewCharacterExecutor::BeginPlay()
{
	Super::BeginPlay();

}
void ARPGCommonNewCharacterExecutor::Update(TSharedPtr<FJsonObject>& RestMsg)
{
	auto Field = RestMsg->TryGetField("ResultCode");
	if (Field == nullptr)
		return;
	FString resultState = Field->AsString();
	ARPGIntroController* CurrentController = Cast<ARPGIntroController>(GetWorld()->GetFirstPlayerController());
	URPGIntroBaseWidget* CurrentWidget = CurrentController->GetUIManager()->GetCurrentWidget();
	if (resultState == SUCCESSD_REST_API)
	{
		auto CharacterInfo = RestMsg->TryGetField("CharacterInfo");
		if (CharacterInfo == nullptr)
			return;
		auto CharacterArray = CharacterInfo->AsArray();
		CurrentController->RequestLobbyScarecrowCreating(CharacterArray);
		
		URPGIntroCreateCharacterLayout* CurrentLayout = Cast<URPGIntroCreateCharacterLayout>(CurrentWidget->GetIntroSwitcher()->GetActiveWidget());
		auto InputCharacterLayout = Cast<IRPGCommonChangeScene>(CurrentLayout->GetInputCharacterLayout());
		InputCharacterLayout->OnChangeWidget();

		URPGIntroBaseWidget* LobbyWidget = CurrentController->GetUIManager()->GetLobbyWidget();
		auto LayoutList = LobbyWidget->GetIntroLayoutList();
		for (int i = 0; i < LayoutList.Num(); i++)
		{
			IRPGIntroLobbySlotInfo* result = Cast<IRPGIntroLobbySlotInfo>(LayoutList[i]);
			if (result == nullptr)
				continue;
			result->Info = CharacterArray;
		}
	}
	else
	{

	}

}