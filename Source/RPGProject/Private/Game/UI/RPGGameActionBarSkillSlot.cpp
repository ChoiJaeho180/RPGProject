// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/UI/RPGGameActionBarSkillSlot.h"
#include "Components/Image.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"

void URPGGameActionBarSkillSlot::NativeConstruct()
{
	Super::NativeConstruct();

	_KeyText = Cast<UTextBlock>(GetWidgetFromName("KeyText"));
	_IconBorder = Cast<UBorder>(GetWidgetFromName("IconBorder"));
	_CooldownBorder = Cast<UBorder>(GetWidgetFromName("CooldownBorder"));
	_CooldownBorder->SetVisibility(ESlateVisibility::Visible);
	_CooldownMaterial = _CooldownBorder->GetDynamicMaterial();
	Visibility = ESlateVisibility::Visible;
	if (_SkillCoolDownInfo == nullptr) _SkillCoolDownInfo = MakeShareable(new FGameSkillDataCopyInfo);
}

void URPGGameActionBarSkillSlot::SetKeyText(FString InputKey)
{
	_KeyText->SetText(FText::FromString(InputKey));
}

void URPGGameActionBarSkillSlot::SetIcon(UTexture2D* icon)
{
	_IconBorder->SetBrushFromTexture(icon);
	_IconBorder->SetVisibility(ESlateVisibility::Visible);
}

void URPGGameActionBarSkillSlot::Update(const TSharedPtr<FGameSkillDataCopyInfo>& Info)
{
	if (_SkillCoolDownInfo->TimeStamp == Info->TimeStamp) return;
	_SkillCoolDownInfo->CoolDown = Info->CoolDown;
	_SkillCoolDownInfo->CurrentCoolDown = Info->CurrentCoolDown;
	_SkillCoolDownInfo->Identify = Info->Identify;
	_SkillCoolDownInfo->Name = Info->Name;
	_SkillCoolDownInfo->TimeStamp = Info->TimeStamp;
	_SkillCoolDownInfo->SkillState = Info->SkillState;
	if(_SkillCoolDownInfo->SkillState == ESkillState::IMPOSSIBILITY)UpdateCoolDownUI(1);
	else if (_SkillCoolDownInfo->SkillState == ESkillState::ING) UpdateCoolDownUI(_SkillCoolDownInfo->CurrentCoolDown / _SkillCoolDownInfo->CoolDown);
	else UpdateCoolDownUI(0);
}

void URPGGameActionBarSkillSlot::UpdateCoolDownUI(float NewRatio)
{
	 _CooldownMaterial->SetScalarParameterValue(FName("percent"), NewRatio);
	 //UE_LOG(LogTemp, Warning, TEXT("UpdateCoolDownUI, %f"), NewRatio);
}

FString URPGGameActionBarSkillSlot::GetKeyText()
{
	return _KeyText->GetText().ToString();
}
