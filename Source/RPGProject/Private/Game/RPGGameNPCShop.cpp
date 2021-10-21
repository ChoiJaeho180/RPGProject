// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/RPGGameNPCShop.h"
#include "Components/WidgetComponent.h"
#include "Game/UI/RPGGameNPCSaying.h"
#include "Game/Enemy/RPGGameTImer.h"

ARPGGameNPCShop::ARPGGameNPCShop()
{
	static ConstructorHelpers::FClassFinder<URPGGameNPCSaying> UI_HUD(TEXT("WidgetBlueprint'/Game/Blueprints/GameWidgetBP/NPC/NPC_Saying.NPC_Saying_C'"));
	if (UI_HUD.Succeeded())
	{
		_WidgetCompo->SetWidgetClass(UI_HUD.Class);
		_WidgetCompo->SetDrawSize(FVector2D(220.0f, 30.0f));
	}

}

void ARPGGameNPCShop::BeginPlay()
{
	Super::BeginPlay();
	_WidgetCompo->SetRelativeLocation(FVector(60.0f, 0.0f, 220.0f));
	_SpeechSetInterval = 2;
	_SpeechTimer->SetStandardTime(_SpeechSetInterval);
}

