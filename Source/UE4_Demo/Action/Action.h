// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <string>
#include "CoreTypes.h"
#include "SharedPointerInternals.h"
#include "SharedPointer.h"

class AActionComponent;

/**
 * 
 */
class FAction : public TSharedFromThis<FAction>
{
public:
	FAction();
	virtual ~FAction();

	virtual std::string description() const;

	virtual TSharedPtr<FAction> clone() const;

	virtual TSharedPtr<FAction> reverse() const;

	virtual bool isDone() const;

	virtual void startWithTarget(AActionComponent* target);

	virtual void stop();

	virtual void step(float dt);

	virtual AActionComponent* getTarget();

	void	setTarget(AActionComponent* target);

	int32	getTag() const;

	void	 setTag(int32 tag);

	int32	getFlags() const;

	void	setFlags(int32 flags);

protected:
	std::string			m_strDesc;
	AActionComponent*	m_pTarget;
	int32				m_nFlags;
	int32				m_nTag;
	bool				m_bIsPaused;
	bool				m_bIsDone;
};
