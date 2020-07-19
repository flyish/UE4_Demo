// Fill out your copyright notice in the Description page of Project Settings.


#include "SequenceAction.h"
#include "Action.h"
#include <memory>

FSequenceAction::FSequenceAction()
	: FParallelAction()
	, m_nIndex( 0 )
{
}

FSequenceAction::~FSequenceAction()
{
}

void FSequenceAction::step(float dt)
{
	if (m_nIndex >= m_childs.size())
	{
		stop();
	}
	else
	{
		std::shared_ptr<FAction> a = m_childs[m_nIndex];
		a->step(dt);
		if (a->isDone())
		{
			++m_nIndex;
		}
	}
}
