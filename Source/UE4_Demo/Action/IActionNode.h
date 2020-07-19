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

	virtual FVector	getScale() const = 0;

	virtual void	setScale(FVector s) = 0;

	virtual void runAction(const std::shared_ptr<FAction>& action) = 0;

	virtual void stopAction(const std::shared_ptr<FAction>& action) = 0;

	virtual void stopAllActions() = 0;

	virtual void pauseAction(const std::shared_ptr<FAction>& action) = 0;

	virtual void pauseAllActions() = 0;

	virtual void resumeAction(const std::shared_ptr<FAction>& action) = 0;

	virtual void resumeAllActions() = 0;
};
