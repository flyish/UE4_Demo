// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "IntvalAction.h"
#include "Vector.h"

/**
 * 
 */
class FScaleAction : public FIntvalAction
{
protected:
	FVector m_srcScale;
	FVector	m_destScale;

public:
	FScaleAction(const FVector& targetScale = FVector(1.0, 1.0, 1.0), float duration = 1.0 );
	~FScaleAction();

	virtual void startWithTarget(IActionNode* target);
	virtual void step(float dt);
};
