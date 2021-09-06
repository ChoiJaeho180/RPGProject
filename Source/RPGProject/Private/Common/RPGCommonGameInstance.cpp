// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/RPGCommonGameInstance.h"

URPGCommonGameInstance::URPGCommonGameInstance()
{

}

void URPGCommonGameInstance::Init()
{
	FRPGCommonRestRequest* RestRequestor = new FRPGCommonRestRequest();
	_RestApiRequestor = TUniquePtr<FRPGCommonRestRequest>(RestRequestor);
}
