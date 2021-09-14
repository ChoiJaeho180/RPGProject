// Fill out your copyright notice in the Description page of Project Settings.
#include "Intro/UI/RPGIntroLobbyWidget.h"
#include "Components/Image.h"
#include "Intro/UI/RPGIntroBaseLayout.h"
#include "Intro/UI/RPGIntroGetChooseScarecrow.h"
#include "Common/RPGCommonGameInstance.h"
#include "Intro/RPGIntroController.h"

#define STRING_EMPTY_NUM 1

void URPGIntroLobbyWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	TMap<EIntroDerivedWidgetState, FString> WidgetStatToIdentifyMap;
	WidgetStatToIdentifyMap.Add(EIntroDerivedWidgetState::LOBBY_INTERACTIVE, FString("WB_Lobby_Interaction_Layout"));
	WidgetStatToIdentifyMap.Add(EIntroDerivedWidgetState::LOBBY_INFO, FString("WB_Lobby_Character_Info_Layout"));
	_RPGIntroSpecificWidgetJudge.SetWidgetIdentifyMap(WidgetStatToIdentifyMap);
}

void URPGIntroLobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();
	int LayoutIndex = _RPGIntroSpecificWidgetJudge.GetUpdateWidgetIndex(_IntroLayoutList, EIntroDerivedWidgetState::LOBBY_INTERACTIVE);
	if (LayoutIndex == -1)
		return;
	_IntroLayoutList[LayoutIndex]->delegateSendWidgetChange.BindUObject(this, &URPGIntroLobbyWidget::OnPreWidgetChange);
}

void URPGIntroLobbyWidget::OnPreWidgetChange(const EIntroUIWidgetState& NewState, const int& ZOrder)
{
	if (NewState == EIntroUIWidgetState::NEXT_LEVEL)
	{
		int LayoutIndex = _RPGIntroSpecificWidgetJudge.GetUpdateWidgetIndex(_IntroLayoutList, EIntroDerivedWidgetState::LOBBY_INFO);
		if (LayoutIndex == -1)
			return;
		IRPGIntroGetChooseScarecrow* ChooseInfo = Cast<IRPGIntroGetChooseScarecrow>(_IntroLayoutList[LayoutIndex]);
		if (ChooseInfo->GetCharacterName().Len() < STRING_EMPTY_NUM)
			return;

		const FString& result = ChooseInfo->GetCharacterName();
		const int& ScarecrowIndex = ChooseInfo->GetScarecrowIndex();

		URPGCommonGameInstance* GameInstance = Cast<URPGCommonGameInstance>(GetGameInstance());
		GameInstance->SetCharacterName(result);
		
		ARPGIntroController* controller = Cast<ARPGIntroController>(GetWorld()->GetFirstPlayerController());
		controller->ChangeEmotionAnim(ScarecrowIndex);
		return;
	}
	ChangeWidget(NewState, 5);
}
