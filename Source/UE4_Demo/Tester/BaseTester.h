// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseTester.generated.h"

UCLASS()
class UE4_DEMO_API ABaseTester : public AActor
{
	GENERATED_BODY()
protected:
	int32 m_nMaxStep;
	int32 m_nCurStep;
	
public:	
	// Sets default values for this actor's properties
	ABaseTester();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, Category = "Tester")
	void prevStep();

	UFUNCTION(BlueprintNativeEvent, Category = "Tester")
	void nextStep();

	UFUNCTION(BlueprintCallable, Category = "Tester")
	virtual void onPrevStep();
	UFUNCTION(BlueprintCallable, Category = "Tester")
	virtual void onNextStep();
};
