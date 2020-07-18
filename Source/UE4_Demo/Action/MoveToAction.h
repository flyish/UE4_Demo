// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "IntvalAction.h"
#include "Vector.h"

/**
 * 
 */
class FMoveToAction : public FIntvalAction
{
protected:
	FVector m_srcPosition;
	FVector	m_destPosition;

public:
	FMoveToAction(const FVector& targetPosition = FVector(), float duration = 1.0 );
	~FMoveToAction();

	virtual void startWithTarget(IActionNode* target);
	virtual void step(float dt);

	virtual void setTargetPosition(const FVector& v);
};
