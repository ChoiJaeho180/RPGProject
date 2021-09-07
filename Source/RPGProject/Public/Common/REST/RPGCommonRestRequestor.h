// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../RPGProject.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Dom/JsonObject.h"
#include "GameFramework/Actor.h"
#include "RPGCommonRestRequestor.generated.h"

DECLARE_DELEGATE_OneParam(FRestApiResponseDelegate, TSharedPtr<FJsonObject>&)

UCLASS()
class RPGPROJECT_API ARPGCommonRestRequestor : public AActor
{
	GENERATED_BODY()
private:
	FHttpModule* _Http;
	FString _ApiBaseUrl = "http://127.0.0.1:3000";
public:	
	// Sets default values for this actor's properties
	ARPGCommonRestRequestor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HttpCall(FString URL, TSharedPtr<FJsonObject> JsonObject);
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
public:
	FRestApiResponseDelegate delegateRestApiResponse;
};
