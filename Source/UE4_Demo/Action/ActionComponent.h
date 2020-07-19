// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Action.h"
#include "ActionWraper.h"
#include "IActionNode.h"
#include "ActionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4_DEMO_API UActionComponent : public UActorComponent, public IActionNode
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

	UFUNCTION(BlueprintCallable, Category = "Action")
	virtual FVector	getScale() const;
	UFUNCTION(BlueprintCallable, Category = "Action")
	virtual void	setScale(FVector s);

	void runAction(const std::shared_ptr<FAction>& action);
	UFUNCTION(BlueprintCallable, Category = "Action")
	void runAction(UActionWraper* action);

	void stopAction(const std::shared_ptr<FAction>& action);
	UFUNCTION(BlueprintCallable, Category = "Action")
	void stopAction(UActionWraper* action);

	UFUNCTION(BlueprintCallable, Category = "Action")
	void stopAllActions();

	void pauseAction(const std::shared_ptr<FAction>& action);
	UFUNCTION(BlueprintCallable, Category = "Action")
	void pauseAction(UActionWraper* action);

	UFUNCTION(BlueprintCallable, Category = "Action")
	void pauseAllActions();

	void resumeAction(const std::shared_ptr<FAction>& action);
	UFUNCTION(BlueprintCallable, Category = "Action")
	void resumeAction(UActionWraper* action);

	UFUNCTION(BlueprintCallable, Category = "Action")
	void resumeAllActions();
};
