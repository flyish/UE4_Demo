// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "ParallelAction.h"

/**
 * 
 */
class FSequenceAction : public FParallelAction
{
	size_t m_nIndex;
public:
	FSequenceAction();
	~FSequenceAction();

	virtual void step(float dt);
};
