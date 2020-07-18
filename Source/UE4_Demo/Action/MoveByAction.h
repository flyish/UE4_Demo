// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "MoveToAction.h"

/**
 * 
 */
class FMoveByAction : public FMoveToAction
{
public:
	FMoveByAction(const FVector& targetPosition = FVector(), float duration = 1.0 );
	~FMoveByAction();


	virtual void startWithTarget(IActionNode* target);
	virtual void setTargetPosition(const FVector& v);
};
