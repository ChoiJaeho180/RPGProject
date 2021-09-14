// Fill out your copyright notice in the Description page of Project Settings.


#include "Intro/RPGIntroScarecrowAnimInstance.h"

void URPGIntroScarecrowAnimInstance::PlayChooseAnim()
{
	if (!Montage_IsPlaying(_ChooseAnim))
	{
		Montage_Play(_ChooseAnim, 1.0f);
	}
}

URPGIntroScarecrowAnimInstance::URPGIntroScarecrowAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>CHOOSE_ANIM(TEXT("AnimMontage'/Game/ParagonGreystone/Characters/Heroes/Greystone/Animations/Emote_Taunt_SwordPoint_T1_Montage.Emote_Taunt_SwordPoint_T1_Montage'"));
	if (CHOOSE_ANIM.Succeeded())
	{
		_ChooseAnim = CHOOSE_ANIM.Object;
	}
}

