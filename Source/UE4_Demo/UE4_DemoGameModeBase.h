// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UE4_DemoGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UE4_DEMO_API AUE4_DemoGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	virtual void StartPlay() override;
};
