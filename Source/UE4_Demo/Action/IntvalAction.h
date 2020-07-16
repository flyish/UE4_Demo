// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Action.h"

/**
 * 
 */
class FIntvalAction : public FAction
{
protected:
	float m_duration;
	float m_elapsed;

public:
	FIntvalAction( float duration = 1.0 );
	~FIntvalAction();

	virtual void step(float dt);

	void setDuration(float duration);
};
