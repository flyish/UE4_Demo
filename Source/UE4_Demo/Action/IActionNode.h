// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <memory>

class FAction;
struct FVector;

class IActionNode
{
public:	
	virtual ~IActionNode() {};

	virtual FVector getLocation() const = 0;

	virtual void	setLocation(const FVector& location) = 0;

	virtual void runAction(std::shared_ptr<FAction>& action) = 0;

	virtual void stopAction(std::shared_ptr<FAction>& action) = 0;

	virtual void stopAllActions() = 0;

	virtual void pauseAction(std::shared_ptr<FAction>& action) = 0;

	virtual void pauseAllActions() = 0;

	virtual void resumeAction(std::shared_ptr<FAction>& action) = 0;

	virtual void resumeAllActions() = 0;
};
