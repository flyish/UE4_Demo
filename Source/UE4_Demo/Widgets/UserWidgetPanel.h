// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidgetPanel.generated.h"

/**
 * 
 */
UCLASS()
class UE4_DEMO_API UUserWidgetPanel : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void PostLoad() override;
	virtual void FinishDestroy() override;
};
