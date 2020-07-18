// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveToAction.h"
#include "IActionNode.h"

FMoveToAction::FMoveToAction(const FVector& targetPosition /*= FVector()*/, float duration/* = 1.0*/)
	: FIntvalAction( duration )
	, m_srcPosition()
	, m_destPosition(targetPosition)
{
}

FMoveToAction::~FMoveToAction()
{
}


void FMoveToAction::startWithTarget(IActionNode* target)
{
	FIntvalAction::startWithTarget(target);

	m_srcPosition = target->getLocation();
}

void FMoveToAction::step(float dt)
{
	FIntvalAction::step(dt);

	if (m_elapsed >= m_duration )
	{
		m_pTarget->setLocation(m_destPosition);
	}
	else
	{
		float p = m_elapsed / m_duration;
		FVector v = FMath::Lerp(m_srcPosition, m_destPosition, p );
		m_pTarget->setLocation(v);
	}
}

void FMoveToAction::setTargetPosition(const FVector& v)
{
	m_destPosition = v;
}
