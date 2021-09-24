// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameUIManager.h"
#include "Game/RPGGameController.h"
#include "Common/UI/RPGCommonFade.h"

// Sets default values
ARPGGameUIManager::ARPGGameUIManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<URPGCommonFade>INTRO_FADE_WIDGET(TEXT("WidgetBlueprint'/Game/Blueprints/WB_Fade.WB_Fade_C'"));
	if (INTRO_FADE_WIDGET.Succeeded())
	{
		_IntroFadeClass = INTRO_FADE_WIDGET.Class;
	}

}

void ARPGGameUIManager::Initialize(ARPGGameController* NewController)
{
	_CurrentController = NewController;
	_GameFadeEffect = CreateWidget<URPGCommonFade>(_CurrentController, _IntroFadeClass);
	_GameFadeEffect->delegateAttachWidget.BindUObject(this, &ARPGGameUIManager::ChangeWidget);
	
	_GameFadeEffect->AddToViewport(5);
	((URPGCommonFade*)_GameFadeEffect)->SetFadeState(ECommonFadeState::FADE_OUT);
	
	//IRPGCommonChangeLevel* FadeChangeLevel = Cast<IRPGCommonChangeLevel>(_IntroFadeEffect);
	//FadeChangeLevel->delegateChangeLevel.BindUObject(this, &ARPGGameUIManager::SendChangeLevel);
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

