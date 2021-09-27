// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/RPGGameNPCShop.h"
#include "Components/WidgetComponent.h"
#include "Game/UI/RPGGameNPCSaying.h"

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
	
}

void ARPGGameNPCShop::SetSpeech()
{
	auto NPCWidget = Cast<URPGGameNPCSaying>(_WidgetCompo->GetUserWidgetObject());
	NPCWidget->NativeConstruct();
	if (NPCWidget != nullptr)
	{
		NPCWidget->SetSpeechTexts(_Speech);
	}
}
