// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Action.h"
#include "ActionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4_DEMO_API UActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION( BlueprintCallable, Category="Action" )
	FVector getLocation() const;

	UFUNCTION(BlueprintCallable, Category = "Action")
	void	setLocation(const FVector& location);

	void runAction(std::shared_ptr<FAction>& action);
	UFUNCTION(BlueprintCallable, Category = "Action")
	void runAction(UActionWraper* action);

	void stopAction(std::shared_ptr<FAction>& action);
	UFUNCTION(BlueprintCallable, Category = "Action")
	void stopAction(UActionWraper* action);

	UFUNCTION(BlueprintCallable, Category = "Action")
	void stopAllActions();

	void pauseAction(std::shared_ptr<FAction>& action);
	UFUNCTION(BlueprintCallable, Category = "Action")
	void pauseAction(UActionWraper* action);

	UFUNCTION(BlueprintCallable, Category = "Action")
	void pauseAllActions();

	void resumeAction(std::shared_ptr<FAction>& action);
	UFUNCTION(BlueprintCallable, Category = "Action")
	void resumeAction(UActionWraper* action);

	UFUNCTION(BlueprintCallable, Category = "Action")
	void resumeAllActions();
};
