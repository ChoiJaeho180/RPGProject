// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/Animation/Enemy/RPGGameEnemyAttackHitCheckNotify.h"
#include "Game/Animation/Enemy/RPGGameEnemyBaseAnim.h"
#include "Game/Enemy/RPGGameEnemyBase.h"
#include "DrawDebugHelpers.h"
#include "Game/RPGGameCharacter.h"
#include "Game/RPGGameController.h"
#include "Game/Enemy/RPGGameEnemyStatComponent.h"
#include "Game/RPGGamePlayerState.h"

void URPGGameEnemyAttackHitCheckNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ARPGGameEnemyBase* Enemy = Cast<ARPGGameEnemyBase>(MeshComp->GetOwner());
	URPGGameEnemyBaseAnim* Anim = Cast<URPGGameEnemyBaseAnim>(MeshComp->GetAnimInstance());
	if (!::IsValid(Anim)) return;

	FHitResult HitResult;
	//FCollisionQueryParams Params2(NAME_None, FCollisionQueryParams::GetUnknownStatId());
	FCollisionQueryParams Params(NAME_None, false, Enemy);

	FVector BastAttackPosition = MeshComp->GetSocketLocation(FName("BaseAttack"));
	bool bResult = Enemy->GetWorld()->SweepSingleByChannel(
		HitResult,
		// 도형의 탐색 영역
		Enemy->GetActorLocation(),
		BastAttackPosition,
		FQuat::Identity,
		// Attack 트레이스 채널
		ECollisionChannel::ECC_GameTraceChannel5,
		// 탐색할 도형 : 50cm 반지름 구체
		FCollisionShape::MakeSphere(100),
		// 공격 명령을 내리는 자신은 이 탐색에 감지되지 않도록 설정
		Params);

	if (bResult == true)
	{
		ARPGGameCharacter* Character = Cast<ARPGGameCharacter>(HitResult.Actor);
		ARPGGamePlayerState* PlayerState = Cast<ARPGGamePlayerState>(Character->GetPlayerState());
		UE_LOG(LogTemp, Warning, TEXT("Hit!!!!!!!"));
		FVector CharacterToEnemyDir = (Enemy->GetActorLocation() - Character->GetActorLocation()).GetSafeNormal();
		float dot = FVector::DotProduct(Character->GetActorForwardVector(), CharacterToEnemyDir);
		float angle = FMath::RadiansToDegrees(FMath::Acos(dot));
		FVector crossPrdt = FVector::CrossProduct(Character->GetActorForwardVector(), CharacterToEnemyDir);
		FVector HitDir = GetAngleToDir(crossPrdt, angle);
		PlayerState->AddHP(-Enemy->GetEnemyStatCompo()->GetAttack());
		if (PlayerState->GetCharacterHP() == 0) Character->Dead();

		Cast<ARPGGameController>(Character->GetController())->PlayerCameraManager->PlayCameraShake(Character->MyShake);
		Character->GetHitting(HitDir);
	}
	//
	//DrawDebugSphere(Anim->GetWorld(), test, 20, 16, FColor::Green, false, 0.2f);
}


FString URPGGameEnemyAttackHitCheckNotify::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}

FVector URPGGameEnemyAttackHitCheckNotify::GetAngleToDir(FVector Cross, float Angle)
{
	if (Cross.Z < 0) Angle = Angle * -1;
	UE_LOG(LogTemp, Warning, TEXT("%f"), Angle);
	if (Angle > -45 && 45 >= Angle)
	{
		//forward
		UE_LOG(LogTemp, Warning, TEXT("FORWARD"));
		return FVector::ForwardVector;
	}
	else if (Angle > 45 && 135 >= Angle)
	{
		// Right

		UE_LOG(LogTemp, Warning, TEXT("RIGHT"));
		return FVector::RightVector;
	}
	else if (Angle > -135  && -45 > Angle)
	{
		// Left

		UE_LOG(LogTemp, Warning, TEXT("LEFT"));
		return FVector::LeftVector;
	}
	else
	{
		// Down

		UE_LOG(LogTemp, Warning, TEXT("Down"));
		return FVector::DownVector;
	}
}
