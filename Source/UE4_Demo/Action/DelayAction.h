// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "IntvalAction.h"

/**
 * 
 */
class FDelayAction : public FIntvalAction
{
public:
	FDelayAction( float delay );
	~FDelayAction();
};
