// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <unordered_map>
#include <set>

class FAction;
class UActionComponent;

/**
 * 
 */
class FActionManager
{
protected:
	typedef std::set< TSharedPtr<FAction, ESPMode::NotThreadSafe> > ActionList;

	ActionList	m_runActions;
	ActionList	m_pausedList;

public:
	FActionManager();
	virtual ~FActionManager();

	virtual void addAction(TSharedPtr<FAction, ESPMode::NotThreadSafe>& action, bool paused);
	virtual void removeAction(TSharedPtr<FAction, ESPMode::NotThreadSafe>& action);
	virtual void removeActionsByTarget(UActionComponent* target);
	virtual void removeAllActions();
	virtual void removeActionsByTag(int32 tag, UActionComponent* target);
	virtual void removeActionsByFlags(int32 flags, UActionComponent* target);

	virtual TSharedPtr<FAction, ESPMode::NotThreadSafe> getActionByTag(int32 tag, UActionComponent* target) const;

	virtual void 	pauseTarget(UActionComponent* target);	
	virtual void 	resumeTarget(UActionComponent* target);

	virtual void 	pauseAllActions();
	virtual void 	resumeAllActions();

	virtual void 	update(float dt);
};
