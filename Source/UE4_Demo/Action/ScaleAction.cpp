// Fill out your copyright notice in the Description page of Project Settings.


#include "ScaleAction.h"
#include "IActionNode.h"

FScaleAction::FScaleAction(const FVector& targetScale, float duration/* = 1.0*/)
	: FIntvalAction( duration )
	, m_srcScale(1.0,1.0, 1.0)
	, m_destScale(targetScale)
{
}

FScaleAction::~FScaleAction()
{
}


void FScaleAction::startWithTarget(IActionNode* target)
{
	FIntvalAction::startWithTarget(target);

	m_srcScale = target->getScale();
}

void FScaleAction::step(float dt)
{
	FIntvalAction::step(dt);

	if (m_elapsed >= m_duration )
	{
		m_pTarget->setScale(m_destScale);
	}
	else
	{
		float p = m_elapsed / m_duration;
		FVector v = FMath::Lerp(m_srcScale, m_destScale, p );
		m_pTarget->setScale(v);
	}
}