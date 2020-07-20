// Fill out your copyright notice in the Description page of Project Settings.

#include "HelperBlueprintFunctionLibrary.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "../UE4_DemoGameModeBase.h"

APlayerController* UHelperBlueprintFunctionLibrary::GetFirstPlayerController(const UObject* WorldContextObject)
{
	return UGameplayStatics::GetPlayerController(WorldContextObject, 0);
}

ACharacter* UHelperBlueprintFunctionLibrary::GetFirstPlayerCharacter(const UObject* WorldContextObject)
{
	return UGameplayStatics::GetPlayerCharacter(WorldContextObject, 0);
}

APawn* UHelperBlueprintFunctionLibrary::GetFirstPlayerPawn(const UObject* WorldContextObject)
{
	return UGameplayStatics::GetPlayerPawn(WorldContextObject, 0);
}

UTesterController* UHelperBlueprintFunctionLibrary::testerController()
{
	AUE4_DemoGameModeBase* pGameBase_ = Cast<AUE4_DemoGameModeBase>(GEngine->GetWorld()->GetAuthGameMode());
	verify(pGameBase_);

	UTesterController* pTesterContrller = pGameBase_->testerController();
	check(pTesterContrller);
	return pTesterContrller;
}
