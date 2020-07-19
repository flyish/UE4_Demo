// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "InstantAction.h"
#include "Delegate.h"

DECLARE_DELEGATE(FActionDelegate);
DECLARE_DELEGATE_OneParam(FActionDelegateEx, void*);

/**
 * 
 */
class FCallbackAction : public FInstantAction
{
public:

public:
	FActionDelegate m_callback;
public:
	FCallbackAction(FActionDelegate callback);
	~FCallbackAction();

	virtual void step(float dt);
};

class FCallbackActionEx : public FInstantAction
{
public:
	FActionDelegateEx m_callback;
	void* m_pContext;
public:
	FCallbackActionEx(FActionDelegateEx callback, void* pContext);
	~FCallbackActionEx();

	virtual void step(float dt);
};