// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ActionBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class UE4_DEMO_API UActionBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Action")
	static	void stopAllActions();

	UFUNCTION(BlueprintCallable, Category = "Action")
	static void pauseAllActions();

	UFUNCTION(BlueprintCallable, Category = "Action")
	static	void resumeAllActions();
};
