// Fill out your copyright notice in the Description page of Project Settings.

#include "HelperBlueprintFunctionLibrary.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

APlayerController* UHelperBlueprintFunctionLibrary::GetFirstPlayerController(const UObject* WorldContextObject)
{
	return UGameplayStatics::GetPlayerController(WorldContextObject, 0);
}

ACharacter* UHelperBlueprintFunctionLibrary::GetFirstPlayerCharacter(const UObject* WorldContextObject)
{
	return UGameplayStatics::GetPlayerCharacter(WorldContextObject, 0);
}
