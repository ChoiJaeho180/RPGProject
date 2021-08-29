#include "../../../Public/Intro/UI/RPGIntroTitleWidget.h"
#include "Animation/WidgetAnimation.h"
#include "Components/Button.h"

void URPGIntroTitleWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayAnimations();

	_StartGameButton = Cast<UButton>(GetWidgetFromName(TEXT("StartGameButton")));
	_StartGameButton->OnClicked.AddDynamic(this, &URPGIntroTitleWidget::OnStartClicked);
}

void URPGIntroTitleWidget::PlayAnimations()
{
	UWidgetBlueprintGeneratedClass* WidgetClass = GetWidgetTreeOwningClass();
	for (int i = 0; i < WidgetClass->Animations.Num(); i++)
	{
		if (WidgetClass->Animations[i]->GetName() != TEXT("TitleAnimation_INST"))
			continue;
		
		PlayAnimation(WidgetClass->Animations[i]);
		break;
	}
}

void URPGIntroTitleWidget::OnStartClicked()
{
}
