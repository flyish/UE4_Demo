// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Action.h"

/**
 * 
 */
class FActionManager
{
public:
	FActionManager();
	~FActionManager();

	virtual void addAction(TSharedPtr<FAction>& action, AActionComponent* target, bool paused);
	virtual void removeAction(TSharedPtr<FAction>& action);
	virtual void remoteActionsByTarget(AActionComponent* target);
	virtual void removeAllActions();
	virtual void remoteActionsByTag(int32 tag, AActionComponent* target);
	virtual void remoteActionsByFlags(int32 flags, AActionComponent* target);

	virtual TSharedPtr<FAction> getActionByTag(int32 tag, AActionComponent* target) const;

	virtual void 	pauseTarget(AActionComponent* target);	
	virtual void 	resumeTarget(AActionComponent* target);

	virtual void 	pauseAllActions();
	virtual void 	resumeAllActions();

	virtual void 	update(float dt);
};
