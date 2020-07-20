// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/UserWidgetPanel.h"
#include "DescPanel.generated.h"

/**
 * 
 */
UCLASS()
class UE4_DEMO_API UDescPanel : public UUserWidgetPanel
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, Category = "DescPanel")
	void setTestDesc(int32 step, int32 maxstep, const FString& desc);
};
