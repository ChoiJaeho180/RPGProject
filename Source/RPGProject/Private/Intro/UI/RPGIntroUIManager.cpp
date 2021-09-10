// Fill out your copyright notice in the Description page of Project Settings.
#include "Intro/UI/RPGIntroUIManager.h"
#include "Intro/UI/RPGIntroMainWidget.h"
#include "Intro/RPGIntroController.h"
#include "Intro/UI/RPGIntroLobbyWidget.h"
#include "Intro/UI/RPGIntroCreateWidget.h"
#include "Common/UI/RPGCommonFade.h"
#include "Common/UI/RPGCommonBaseEffect.h"
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
	static ConstructorHelpers::FClassFinder<URPGIntroCreateWidget>INTRO_CREATE_WIDGET(TEXT("WidgetBlueprint'/Game/Blueprints/IntroWidgetBP/WB_Create.WB_Create_C'"));
	if (INTRO_CREATE_WIDGET.Succeeded())
	{
		_IntroCreateWidgetClass = INTRO_CREATE_WIDGET.Class;
	}
	static ConstructorHelpers::FClassFinder<URPGCommonFade>INTRO_FADE_WIDGET(TEXT("WidgetBlueprint'/Game/Blueprints/WB_Fade.WB_Fade_C'"));
	if (INTRO_FADE_WIDGET.Succeeded())
	{
		_IntroFadeClass = INTRO_FADE_WIDGET.Class;
	}
	
}

// Called when the game starts or when spawned
void ARPGIntroUIManager::BeginPlay()
{
	Super::BeginPlay();

	_IntroCurrentWidgetState = EIntroUIWidgetState::MAIN;
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

	URPGIntroBaseWidget* IntroCreateWidget = CreateWidget<URPGIntroCreateWidget>(_CurrentController, _IntroCreateWidgetClass);
	IntroCreateWidget->delegateChangeUI.BindUObject(this, &ARPGIntroUIManager::UpdateWidget);
	_IntroWidgetMap.Add(EIntroUIWidgetState::CREATE, IntroCreateWidget);
	
	_IntroFadeEffect = CreateWidget<URPGCommonFade>(_CurrentController, _IntroFadeClass);
	_IntroFadeEffect->delegateAttachWidget.BindUObject(this, &ARPGIntroUIManager::ChangeWidget);
	_IntroFadeEffect->AddToViewport(5);
	ChangeWidget();
}

void ARPGIntroUIManager::UpdateWidget(const EIntroUIWidgetState& NewWidgetState)
{
	_IntroFadeEffect->PlayAnim();
	_IntroCurrentWidgetState = NewWidgetState;
}

void ARPGIntroUIManager::ChangeWidget()
{
	if (_IntroWidgetMap.Num() == 0)
		return;
	if (_IntroWidgetMap.Contains(_IntroCurrentWidgetState) == false)
		return;

	_CurrentController->SetPlayerStart(_IntroCurrentWidgetState);
	_IntroWidgetMap[_IntroCurrentWidgetState]->AddToViewport(0);
	if (_IntroCurrentWidget != nullptr)
	{
		if(_IntroCurrentWidget->GetName() != FString("None"))
			_IntroCurrentWidget->RemoveFromViewport();
	}
	_IntroCurrentWidget = _IntroWidgetMap[_IntroCurrentWidgetState];
}

URPGIntroBaseWidget* ARPGIntroUIManager::GetCurrentWidget() const
{
	return _IntroCurrentWidget;
}

