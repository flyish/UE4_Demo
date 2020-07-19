// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "InstantAction.h"
#include <memory>
#include <vector>

/**
 * 
 */
class FParallelAction : public FInstantAction
{
protected:
	std::vector< std::shared_ptr<FAction> > m_childs;

public:
	FParallelAction();
	~FParallelAction();

	virtual void startWithTarget(IActionNode* target);
	virtual void step(float dt);

	void addAction(const std::shared_ptr<FAction>& child);
};
