// Fill out your copyright notice in the Description page of Project Settings.
#include "Intro/UI/RPGIntroUIManager.h"
#include "Intro/UI/RPGIntroMainWidget.h"
#include "Intro/RPGIntroController.h"
#include "Intro/UI/RPGIntroLobbyWidget.h"
// Sets default values
ARPGIntroUIManager::ARPGIntroUIManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FClassFinder<URPGIntroMainWidget>INTRO_MAIN_WIDGET(TEXT("WidgetBlueprint'/Game/Blueprints/IntroWidgetBP/WB_Main.WB_Main_C'"));
	if (INTRO_MAIN_WIDGET.Succeeded())
	{
		_IntroTitleWidgetClass = INTRO_MAIN_WIDGET.Class;
	}
	static ConstructorHelpers::FClassFinder<URPGIntroLobbyWidget>INTRO_LOBBY_WIDGET(TEXT("WidgetBlueprint'/Game/Blueprints/IntroWidgetBP/WB_Lobby.WB_Lobby_C'"));
	if (INTRO_LOBBY_WIDGET.Succeeded())
	{
		_IntroLobbyWidgetClass = INTRO_LOBBY_WIDGET.Class;
	}
}

// Called when the game starts or when spawned
void ARPGIntroUIManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARPGIntroUIManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARPGIntroUIManager::Initialize(ARPGIntroController* NewController)
{
	_CurrentController = NewController;
	if (_CurrentController == nullptr)
		return;
	
	URPGIntroBaseWidget* IntroMainWidget = CreateWidget<URPGIntroMainWidget>(_CurrentController, _IntroTitleWidgetClass);
	IntroMainWidget->delegateChangeUI.BindUObject(this, &ARPGIntroUIManager::UpdateWidget);
	_IntroWidgetMap.Add(EIntroUIWidgetState::MAIN, IntroMainWidget);
	URPGIntroBaseWidget* IntroLobbyWidget = CreateWidget<URPGIntroLobbyWidget>(_CurrentController, _IntroLobbyWidgetClass);
	IntroLobbyWidget->delegateChangeUI.BindUObject(this, &ARPGIntroUIManager::UpdateWidget);
	_IntroWidgetMap.Add(EIntroUIWidgetState::LOBBY, IntroLobbyWidget);

	UpdateWidget(EIntroUIWidgetState::MAIN);
}

void ARPGIntroUIManager::UpdateWidget(const EIntroUIWidgetState& NewWidgetState)
{
	_IntroWidgetMap[NewWidgetState]->AddToViewport();
	if (_IntroCurrentWidget != nullptr)
	{
		_IntroCurrentWidget->RemoveFromViewport();
	}
	_IntroCurrentWidget = _IntroWidgetMap[NewWidgetState];
}

