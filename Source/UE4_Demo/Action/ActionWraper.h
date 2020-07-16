// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Action.h"
#include "ActionWraper.generated.h"

/**
 * 
 */
UCLASS()
class UE4_DEMO_API UActionWraper : public UObject
{
	GENERATED_BODY()
	
private:
	std::shared_ptr<FAction> m_realAction;

public:
	//UActionWraper(std::shared_ptr<FAction>& action);

	std::shared_ptr<FAction>& realAction();
	const std::shared_ptr<FAction>& realAction() const;

	void attach(std::shared_ptr<FAction>& action);
	std::shared_ptr<FAction> detach();

	UFUNCTION(BlueprintPure, Category = "Action")
	static UActionWraper* createMoveToAction(const FVector& targetPosition, float duraion = 1.0f);

	UFUNCTION(BlueprintPure, Category = "Action")
	static UActionWraper* createMoveByAction(const FVector& offsetPosition, float duraion = 1.0f);
};
