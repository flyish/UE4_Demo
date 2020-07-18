// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveByAction.h"
#include "ActionComponent.h"

FMoveByAction::FMoveByAction(const FVector& targetPosition /*= FVector()*/, float duration/* = 1.0*/)
	: FMoveToAction( FVector(), duration )
{
	setTargetPosition(targetPosition);
}

FMoveByAction::~FMoveByAction()
{
}


void FMoveByAction::startWithTarget(IActionNode* target)
{
	FMoveToAction::startWithTarget(target);

	if (!m_destPosition.IsZero())
	{
		m_destPosition = m_srcPosition + m_destPosition;
	}
}

void FMoveByAction::setTargetPosition(const FVector& v)
{
	if (nullptr != m_pTarget)
	{
		// calc target position 
		m_destPosition = m_srcPosition + v;
	}
	else
	{
		// set target position is offset position if not set target
		m_destPosition = v;
	}
}

