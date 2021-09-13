// Fill out your copyright notice in the Description page of Project Settings.
#include "Common/REST/RPGCommonRestLoginExecutor.h"
#include "Intro/RPGIntroController.h"
#include "Intro/UI/RPGIntroUIManager.h"
#include "Intro/UI/RPGIntroBaseWidget.h"
#include "Intro/UI/RPGIntroLoginLayout.h"
#include "Components/WidgetSwitcher.h"
#include "Common/UI/RPGCommonFailedEvent.h"
#include "Common/RPGCommonGameInstance.h"
#include "Intro/UI/RPGIntroBaseLayout.h"
#include "Intro/UI/RPGIntroLobbySlotInfo.h"

// Sets default values
ARPGCommonRestLoginExecutor::ARPGCommonRestLoginExecutor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	_RestMsgIdentify = FString("LOGIN");
}

// Called when the game starts or when spawned
void ARPGCommonRestLoginExecutor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARPGCommonRestLoginExecutor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARPGCommonRestLoginExecutor::Update(TSharedPtr<FJsonObject>& RestMsg)
{
	auto Field = RestMsg->TryGetField("ResultCode");
	if (Field == nullptr)
		return;
	FString resultState = Field->AsString();
	ARPGIntroController* CurrentController = Cast<ARPGIntroController>(GetWorld()->GetFirstPlayerController());
	URPGIntroBaseWidget* CurrentWidget = CurrentController->GetUIManager()->GetCurrentWidget();
	if (resultState == SUCCESSD_REST_API)
	{
		auto TokenValue = RestMsg->TryGetField("Token");
		if (TokenValue == nullptr)
			return;
		delgateSetToken.ExecuteIfBound(TokenValue->AsString());
		auto CharacterInfo = RestMsg->TryGetField("CharacterInfo");
		if (CharacterInfo == nullptr)
			return;

		auto CharacterArray = CharacterInfo->AsArray();
		CurrentController->RequestLobbyScarecrowCreating(CharacterArray);
		IRPGCommonChangeScene* CurrentLayout = Cast<IRPGCommonChangeScene>(CurrentWidget->GetIntroSwitcher()->GetActiveWidget());
		CurrentLayout->OnChangeWidget();

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
		IRPGCommonFailedEvent* CurrentLayout = Cast<IRPGCommonFailedEvent>(CurrentWidget->GetIntroSwitcher()->GetActiveWidget());
		CurrentLayout->RegistFailedEvent();
	}
}

