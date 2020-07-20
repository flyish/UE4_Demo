// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "../Widgets/UserWidgetPanel.h"
#include "WidgetBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class UE4_DEMO_API UWidgetBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Widget Manager")
	static void showWidget(const FString& path, uint8 showType, const FString& associatedName, bool create = true);
	UFUNCTION(BlueprintCallable, Category = "Widget Manager")
	static void hideWidget(const FString& path, uint8 hideType);
	UFUNCTION(BlueprintCallable, Category = "Widget Manager")
	static UUserWidgetsManager* widgetsManager();
};
