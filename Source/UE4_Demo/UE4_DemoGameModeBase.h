// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Action/ActionManager.h"
#include "Widgets/UserWidgetsManager.h"
#include "Tester/TesterController.h"
#include "UE4_DemoGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UE4_DEMO_API AUE4_DemoGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	FActionManager* m_pActionManager;
	UPROPERTY(EditAnywhere, Category = "Manager")
	UUserWidgetsManager* m_pUserWidgetManager;
	UPROPERTY(EditAnywhere, Category = "Manager")
	UTesterController*	 m_pTesterController;
public:

	AUE4_DemoGameModeBase();
	~AUE4_DemoGameModeBase();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	virtual void StartPlay() override;
	virtual void BeginDestroy() override;

	FActionManager* actionManager();

	UFUNCTION(BlueprintPure, Category = "UserWidgets")
	UUserWidgetsManager* userWidgetsManager();

	UFUNCTION(BlueprintPure, Category = "Tester")
	UTesterController* testerController();
};
