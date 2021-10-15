// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/Animation/RPGGameCharacterDeadNotify.h"
#include "Game/RPGGameCharacter.h"
#include "Game/RPGGameController.h"
#include "Common/RPGCommonGameInstance.h"
#include "Game/RPGGameDataTableManager.h"

void URPGGameCharacterDeadNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ARPGGameCharacter* Character = Cast<ARPGGameCharacter>(MeshComp->GetOwner());
	if (!::IsValid(Character)) return;
	ARPGGameController* Controller = Cast<ARPGGameController>(Character->GetController());
	if (!::IsValid(Controller)) return;

	URPGGameDataTableManager* DTManager = Cast<URPGCommonGameInstance>(Character->GetWorld()->GetGameInstance())->GetDataTableManager();
	TArray<FPortalInfo*> PortalInfo = DTManager->GetPortalNameToData("Desert");
	Character->SetNextMap(PortalInfo[0]->NextMap);
	Character->SetNextMapPosition(PortalInfo[0]->NextPosition);
	UE_LOG(LogTemp, Warning, TEXT("%f, %f, %f"), Character->GetNextMapPosition().X, Character->GetNextMapPosition().Y, Character->GetNextMapPosition().Z);
	Controller->PreChangeMap();
}

FString URPGGameCharacterDeadNotify::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}
