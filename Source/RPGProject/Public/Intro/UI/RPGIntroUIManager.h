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
class URPGIntroCreateWidget;

UCLASS()
class RPGPROJECT_API ARPGIntroUIManager : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	ARPGIntroController* _CurrentController;
	UPROPERTY()
	URPGIntroBaseWidget* _IntroCurrentWidget;
	UPROPERTY()
	TMap<EIntroUIWidgetState, URPGIntroBaseWidget*> _IntroWidgetMap;
	UPROPERTY()
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
	UFUNCTION()
	void PreChangeLevel();
	void SendChangeLevel();
public:
	URPGIntroBaseWidget* GetCurrentWidget() const;
	URPGIntroBaseWidget* GetLobbyWidget() const;
public:
	TSubclassOf<URPGIntroMainWidget> _IntroTitleWidgetClass;
	TSubclassOf<URPGIntroLobbyWidget> _IntroLobbyWidgetClass;
	TSubclassOf<URPGIntroCreateWidget> _IntroCreateWidgetClass;
	TSubclassOf<URPGCommonFade> _IntroFadeClass;
};
