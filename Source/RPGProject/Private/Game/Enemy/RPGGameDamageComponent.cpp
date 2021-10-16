// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/Enemy/RPGGameDamageComponent.h"
#include "Components/WidgetComponent.h"
#include "Game/UI/RPGGameDamagerWidget.h"

// Sets default values for this component's properties
URPGGameDamageComponent::URPGGameDamageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<UUserWidget> DAMAGE_HUD(TEXT("WidgetBlueprint'/Game/Blueprints/GameWidgetBP/Common/DamagaWidget.DamagaWidget_C'"));
	if (DAMAGE_HUD.Succeeded())
	{
		DamageWidgetClass = DAMAGE_HUD.Class;
	}


	// ...
}


// Called when the game starts
void URPGGameDamageComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URPGGameDamageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void URPGGameDamageComponent::AttachWidget(int Damage, APlayerController* Controller, FVector MonsterLocation)
{
	FVector2D result;
	Controller->ProjectWorldLocationToScreen(MonsterLocation, result);
	URPGGameDamagerWidget* DamageWidget = CreateWidget<URPGGameDamagerWidget>(Controller, DamageWidgetClass);
	
	result.X -= 100;
	result.Y -= 25;
	DamageWidget->SetInitPosition(result);
	DamageWidget->SetPositionInViewport(result);
	result.Y -= 70;
	DamageWidget->SetGoalPosition(result);
	DamageWidget->AddToViewport();

	DamageWidget->SetDamageText(FString::FromInt(Damage));
	DamageWidget->PlayFadeAnimation();

}

