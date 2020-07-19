// Fill out your copyright notice in the Description page of Project Settings.


#include "CallBackAction.h"

FCallbackAction::FCallbackAction(FActionDelegate callback)
	: m_callback( callback )
{
}

FCallbackAction::~FCallbackAction()
{
}

void FCallbackAction::step(float dt)
{
	m_callback.ExecuteIfBound();
	FInstantAction::stop();
}


FCallbackActionEx::FCallbackActionEx(FActionDelegateEx callback, void* pContext)
	: m_callback(callback)
	, m_pContext( pContext )
{
}

FCallbackActionEx::~FCallbackActionEx()
{
}

void FCallbackActionEx::step(float dt)
{
	m_callback.ExecuteIfBound(m_pContext);
	FInstantAction::stop();
}