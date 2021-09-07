// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "GameFramework/Actor.h"
#include "RPGIntroUIManager.generated.h"

class URPGIntroBaseWidget;
class URPGIntroMainWidget;
class URPGIntroLobbyWidget;
class ARPGIntroController;
class URPGCommonFade;
class URPGCommonBaseEffect;

UCLASS()
class RPGPROJECT_API ARPGIntroUIManager : public AActor
{
	GENERATED_BODY()
	
private:
	ARPGIntroController* _CurrentController;
	URPGIntroBaseWidget* _IntroCurrentWidget;
	TMap<EIntroUIWidgetState, URPGIntroBaseWidget*> _IntroWidgetMap;
	URPGCommonBaseEffect* _IntroFadeEffect;
	EIntroUIWidgetState _IntroCurrentWidgetState;
public:	
	// Sets default values for this actor's properties
	ARPGIntroUIManager();
	void Initialize(ARPGIntroController* NewController);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void UpdateWidget(const EIntroUIWidgetState& NewWidgetState);
	UFUNCTION()
	void ChangeWidget();
public:
	URPGIntroBaseWidget* GetCurrentWidget() const;
	
public:
	TSubclassOf<URPGIntroMainWidget> _IntroTitleWidgetClass;
	TSubclassOf<URPGIntroLobbyWidget> _IntroLobbyWidgetClass;
	TSubclassOf<URPGCommonFade> _IntroFadeClass;
};
