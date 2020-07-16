// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionWraper.h"
#include "MoveToAction.h"
#include "MoveByAction.h"

//UActionWraper::UActionWraper(std::shared_ptr<FAction>& action)
//	: m_realAction( action )
//{
//
//}

std::shared_ptr<FAction>& UActionWraper::realAction()
{
	return m_realAction;
}

const std::shared_ptr<FAction>& UActionWraper::realAction() const
{
	return m_realAction;
}

void UActionWraper::attach(std::shared_ptr<FAction>& action)
{
	m_realAction = action;
}

std::shared_ptr<FAction> UActionWraper::detach()
{
	std::shared_ptr<FAction> p(m_realAction);
	m_realAction.reset();

	return p;
}

UActionWraper* UActionWraper::createMoveToAction(const FVector& targetPosition, float duraion /*= 1.0f*/)
{
	UActionWraper* pWrapper_ = NewObject<UActionWraper>();
	if (NULL != pWrapper_)
	{
		FMoveToAction* pAction_ = new FMoveToAction(targetPosition, duraion);
		std::shared_ptr<FAction> p_ = pAction_->shared_from_this();
		pWrapper_->attach( p_ );
	}

	return pWrapper_;
}

UActionWraper* UActionWraper::createMoveByAction(const FVector& offsetPosition, float duraion /*= 1.0f*/)
{
	UActionWraper* pWrapper_ = NewObject<UActionWraper>();
	if (NULL != pWrapper_)
	{
		FMoveToAction* pAction_ = new FMoveByAction(offsetPosition, duraion);
		std::shared_ptr<FAction> p_ = pAction_->shared_from_this();
		pWrapper_->attach(p_);
	}

	return pWrapper_;
}
