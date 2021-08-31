// Fill out your copyright notice in the Description page of Project Settings.
#include "../../../Public/Intro/UI/RPGIntroUIManager.h"
#include "../../../Public/Intro/UI/RPGIntroMainWidget.h"
#include "../../../Public/Intro/RPGIntroController.h"
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

	_IntroMainWidget = CreateWidget<URPGIntroMainWidget>(_CurrentController, _IntroTitleWidgetClass);
	_IntroMainWidget->AddToViewport();
}

