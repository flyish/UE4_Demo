// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Action/ActionManager.h"
#include "Widgets/UserWidgetsManager.h"
#include "UE4_DemoGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UE4_DEMO_API AUE4_DemoGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	FActionManager* m_pActionManager;
	UUserWidgetsManager* m_pUserWidgetManager;
public:

	AUE4_DemoGameModeBase();
	~AUE4_DemoGameModeBase();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	virtual void StartPlay() override;

	FActionManager* actionManager();

	UFUNCTION(BlueprintPure, Category = "UserWidgets")
	UUserWidgetsManager* userWidgetsManager();
};
