// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <string>
#include <memory>
#include "HAL/Platform.h"
#include "SharedPointerInternals.h"
#include "SharedPointer.h"

class UActionComponent;

/**
 * 
 */
class FAction;
class FAction : public std::enable_shared_from_this<FAction>
{
public:
	FAction();
	virtual ~FAction();

	virtual std::string description() const;

	virtual std::shared_ptr<FAction> clone() const;

	virtual std::shared_ptr<FAction> reverse() const;

	virtual bool isDone() const;

	virtual void startWithTarget(UActionComponent* target);

	virtual void stop();

	virtual void step(float dt);

	virtual UActionComponent* getTarget();

	void	setTarget(UActionComponent* target);

	int32	getTag() const;

	void	 setTag(int32 tag);

	int32	getFlags() const;

	void	setFlags(int32 flags);

protected:
	std::string			m_strDesc;
	UActionComponent*	m_pTarget;
	int32				m_nFlags;
	int32				m_nTag;
	bool				m_bIsDone;
};
