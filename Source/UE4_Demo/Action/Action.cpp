// Fill out your copyright notice in the Description page of Project Settings.


#include "Action.h"
#include "ActionComponent.h"

FAction::FAction()
	: m_pTarget( NULL )
	, m_nFlags( 0 )
	, m_nTag( 0 )
	, m_bIsDone( false )
{

}

FAction::~FAction()
{
}

std::string FAction::description() const
{
	return "";
}

TSharedPtr<FAction, ESPMode::NotThreadSafe> FAction::clone() const
{
	return TSharedPtr<FAction, ESPMode::NotThreadSafe>();
}

TSharedPtr<FAction, ESPMode::NotThreadSafe> FAction::reverse() const
{
	return TSharedPtr<FAction, ESPMode::NotThreadSafe>();
}

bool FAction::isDone() const
{
	return m_bIsDone;
}

void FAction::startWithTarget(UActionComponent* target)
{
	setTarget(target);
}

void FAction::stop()
{
	m_bIsDone = true;
}

void FAction::step(float dt)
{

}

UActionComponent* FAction::getTarget()
{
	return m_pTarget;
}

void FAction::setTarget(UActionComponent* target)
{
	m_pTarget = target;
}

int32 FAction::getTag() const
{
	return m_nTag;
}

void FAction::setTag(int32 tag)
{
	m_nTag = tag;
}

int32 FAction::getFlags() const
{
	return m_nFlags;
}

void FAction::setFlags(int32 flags)
{
	m_nFlags = flags;
}
