// Fill out your copyright notice in the Description page of Project Settings.


#include "IntvalAction.h"

FIntvalAction::FIntvalAction(float duration/* = 1.0*/)
	: m_duration( duration )
	, m_elapsed( 0.f )
{
}

FIntvalAction::~FIntvalAction()
{
}

void FIntvalAction::step(float dt)
{
	m_elapsed += dt;
	if (m_elapsed >= m_duration)
	{
		stop();
	}
}

void FIntvalAction::setDuration(float duration)
{
	m_duration = duration;
}
