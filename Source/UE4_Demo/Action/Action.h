// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <string>
#include "HAL/Platform.h"
#include "SharedPointerInternals.h"
#include "SharedPointer.h"

class UActionComponent;

/**
 * 
 */
class FAction;
class FAction : public TSharedFromThis<FAction, ESPMode::NotThreadSafe>
{
public:
	FAction();
	virtual ~FAction();

	virtual std::string description() const;

	virtual TSharedPtr<FAction, ESPMode::NotThreadSafe> clone() const;

	virtual TSharedPtr<FAction, ESPMode::NotThreadSafe> reverse() const;

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
