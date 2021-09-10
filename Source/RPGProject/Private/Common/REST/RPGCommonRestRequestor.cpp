// Fill out your copyright notice in the Description page of Project Settings.

#include "Common/REST/RPGCommonRestRequestor.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

// Sets default values
ARPGCommonRestRequestor::ARPGCommonRestRequestor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_Http = &FHttpModule::Get();
}

// Called when the game starts or when spawned
void ARPGCommonRestRequestor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARPGCommonRestRequestor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARPGCommonRestRequestor::HttpCall(FString URL, TSharedPtr<FJsonObject>& JsonObject)
{
	TSharedRef<IHttpRequest> Request = _Http->CreateRequest();
	FString OutputString;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);

	Request->OnProcessRequestComplete().BindUObject(this, &ARPGCommonRestRequestor::OnResponseReceived);
	URL = _ApiBaseUrl + URL;
	Request->SetURL(URL);
	Request->SetVerb(FString("Post"));
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->SetContentAsString(OutputString);
	Request->ProcessRequest();
}

void ARPGCommonRestRequestor::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful == false)
		return;

	TSharedPtr<FJsonObject> JsonObject;
	JsonObject.Get();
	TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(Response->GetContentAsString());
	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		delegateRestApiResponse.ExecuteIfBound(JsonObject);
	}
}

