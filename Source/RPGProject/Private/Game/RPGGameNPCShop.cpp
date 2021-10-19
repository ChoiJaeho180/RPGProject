// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/RPGGameNPCShop.h"
#include "Components/WidgetComponent.h"
#include "Game/UI/RPGGameNPCSaying.h"
#include "Game/Enemy/RPGGameTImer.h"

ARPGGameNPCShop::ARPGGameNPCShop()
{

}

void ARPGGameNPCShop::BeginPlay()
{
	Super::BeginPlay();
	_SpeechSetInterval = 2;
	_SpeechTimer->SetStandardTime(_SpeechSetInterval);
}

