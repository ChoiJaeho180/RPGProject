// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameUIManager.h"
#include "Game/RPGGameController.h"
#include "Common/UI/RPGCommonFade.h"
#include "Game/UI/RPGGameMainWidget.h"
#include "Game/UI/RPGGameUIIdeliver.h"
#include "Game/UI/RPGGameGetUserInfo.h"
#include "Game/UI/RPGGameUserLayout.h"

// Sets default values
ARPGGameUIManager::ARPGGameUIManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<URPGCommonFade>INTRO_FADE_WIDGET(TEXT("WidgetBlueprint'/Game/Blueprints/WB_Fade.WB_Fade_C'"));
	if (INTRO_FADE_WIDGET.Succeeded())
	{
		IntroFadeClass = INTRO_FADE_WIDGET.Class;
	}
	static ConstructorHelpers::FClassFinder<URPGGameMainWidget>MAIN_WIDGET(TEXT("WidgetBlueprint'/Game/Blueprints/GameWidgetBP/Character/GameMainWidget.GameMainWidget_C'"));
	if (MAIN_WIDGET.Succeeded())
	{
		GameMainClass = MAIN_WIDGET.Class;
	}
}

void ARPGGameUIManager::Initialize(ARPGGameController* NewController)
{
	_CurrentController = NewController;
	_GameFadeEffect = CreateWidget<URPGCommonFade>(_CurrentController, IntroFadeClass);
	_GameFadeEffect->delegateAttachWidget.BindUObject(this, &ARPGGameUIManager::ChangeWidget);
	_GameFadeEffect->AddToViewport(5);

	((URPGCommonFade*)_GameFadeEffect)->SetFadeState(ECommonFadeState::FADE_OUT);

	_MainWidget = CreateWidget<URPGGameMainWidget>(_CurrentController, GameMainClass);
	_MainWidget->SetLayoutList();
	_MainWidget->AddToViewport(0);
	_MainWidget->ChangeLayout(EGameMainUIType::USER_LAYOUT);
	
	_UIDeliver = NewObject<URPGGameUIIdeliver>();

	URPGGameBaseLayout* GameLayout = _MainWidget->GetUserLayout();
	URPGGameUserLayout* UserLayout = Cast<URPGGameUserLayout>(GameLayout);
	IRPGGameGetUserInfo* GetUSerobj = Cast<IRPGGameGetUserInfo>(UserLayout);
	_UIDeliver->SetDeliveryTargetUI(GetUSerobj->GetUserInfoLayout());
}

void ARPGGameUIManager::InitInventoryAndActionBar(const TArray<FRPGRestItem>& NewItem, const TArray<FRPGRestItem>& RestActionBar)
{
	_UIDeliver->InitInventoryAndActionBar(NewItem, RestActionBar);
}

// Called when the game starts or when spawned
void ARPGGameUIManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARPGGameUIManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARPGGameUIManager::UpdateLevel()
{
	_GameFadeEffect->PlayAnim();
}

void ARPGGameUIManager::ChangeWidget()
{
}

void ARPGGameUIManager::SendInputState(const EInventoryUIType& NewInput)
{
	if (_UIDeliver == nullptr)
		return; 
	UE_LOG(LogTemp, Warning, TEXT("SendInputState"));
	_UIDeliver->SendInputState(NewInput);
}

TSharedPtr<FRPGItemInfo> ARPGGameUIManager::GetInputPortionSlotData(const FString Key)
{
	return _UIDeliver->GetInputPortionSlotInfo(Key);
}

void ARPGGameUIManager::ActiveShop()
{
	_UIDeliver->ActiveShop();
}

