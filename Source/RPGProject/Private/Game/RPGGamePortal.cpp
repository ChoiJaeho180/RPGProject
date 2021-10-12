// Fill out your copyright notice in the Description page of Project Settings.
#include "Game/RPGGamePortal.h"
#include "Game/RPGGameCharacter.h"

// Sets default values
ARPGGamePortal::ARPGGamePortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	_Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("PortalCompo"));
	RootComponent = _Collision;
	_Collision->OnComponentBeginOverlap.AddDynamic(this, &ARPGGamePortal::OnOverlapBegin);
	_Collision->OnComponentEndOverlap.AddDynamic(this, &ARPGGamePortal::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ARPGGamePortal::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARPGGamePortal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ARPGGameCharacter* Character = Cast<ARPGGameCharacter>(OtherActor);
	Character->SetNextMap(_NextMap);
	Character->SetNextMapPosition(_NextPosition);
}

void ARPGGamePortal::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ARPGGameCharacter* Character = Cast<ARPGGameCharacter>(OtherActor);
	Character->SetNextMap(FString(""));
	//Character->SetNextMapPosition(FVector::ZeroVector);
}

void ARPGGamePortal::Init(FPortalInfo* Data)
{
	SetActorLocation(Data->CurrentPosition);
	_NextMap = Data->NextMap;
	_NextPosition = Data->NextPosition;
	SetActorScale3D(FVector(3.f, 3.f, 3.f));
}

// Called every frame
void ARPGGamePortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

