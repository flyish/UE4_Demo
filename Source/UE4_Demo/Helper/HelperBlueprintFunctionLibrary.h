// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ObjectMacros.h"
#include "GameFramework/Actor.h"
#include "HelperBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class UE4_DEMO_API UHelperBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintPure, Category = "Game", meta = (WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"))
	static APlayerController* GetFirstPlayerController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "Game", meta = (WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"))
	static ACharacter* GetFirstPlayerCharacter(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "Game", meta = (WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"))
	static APawn* GetFirstPlayerPawn(const UObject* WorldContextObject);
};
