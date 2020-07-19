// Fill out your copyright notice in the Description page of Project Settings.


#include "ParallelAction.h"

FParallelAction::FParallelAction()
	: FInstantAction()
{
}

FParallelAction::~FParallelAction()
{
}

void FParallelAction::startWithTarget(IActionNode* target)
{
	FInstantAction::startWithTarget(target);

	for (auto& x : m_childs)
	{
		x->startWithTarget(target);
	}
}

void FParallelAction::step(float dt)
{
	bool bFinish = true;

	for(auto& x : m_childs)
	{
		x->step(dt);
		if (bFinish && !x->isDone())
		{
			bFinish = false;
		}
	}

	if (bFinish)
	{
		stop();
	}
}

void FParallelAction::addAction(const std::shared_ptr<FAction>& child)
{
	m_childs.push_back(child);
}
