// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/RPGGameNPCData.h"
#include "Runtime/Engine/Classes/Animation/AnimInstance.h"

// Sets default values
ARPGGameNPCData::ARPGGameNPCData()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	{
		FNPCInfo NPCInfo;
		NPCInfo.Type = "VILLAGE_SHOP_NPC";
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CARDBOARD(TEXT("SkeletalMesh'/Game/ParagonYin/Characters/Heroes/Yin/Meshes/Yin.Yin'"));
		if (SK_CARDBOARD.Succeeded())
		{
			NPCInfo.SkeletalMesh = SK_CARDBOARD.Object;
		}
		static ConstructorHelpers::FClassFinder<UAnimInstance> ANIM_SHOP_NPC(TEXT("AnimBlueprint'/Game/ParagonYin/Characters/Heroes/Yin/Meshes/SHOP_ANIM.SHOP_ANIM_C'"));
		if (ANIM_SHOP_NPC.Succeeded())
		{
			NPCInfo.AnimInstanceClass = ANIM_SHOP_NPC.Class;
		}
		_NPCInfo.Add(NPCInfo);
	}
}

// Called when the game starts or when spawned
void ARPGGameNPCData::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARPGGameNPCData::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARPGGameNPCData::SetNPCInfo(FNPCInfo NewInfo)
{
	for (int i = 0; i < _NPCInfo.Num(); i++)
	{
		if (_NPCInfo[i].Type == NewInfo.Type)
		{
			_NPCInfo[i].Name = NewInfo.Name;
			_NPCInfo[i].Position = NewInfo.Position;
			_NPCInfo[i].Village = NewInfo.Village;
			_NPCInfo[i].bQuest = NewInfo.bQuest; 
			_NPCInfo[i].Speech = NewInfo.Speech;
		}
	}
}

