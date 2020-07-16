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
	typedef std::set< std::shared_ptr<FAction> > ActionList;

	ActionList	m_runActions;
	ActionList	m_pausedList;

public:
	FActionManager();
	virtual ~FActionManager();

	virtual void addAction(std::shared_ptr<FAction>& action, UActionComponent* target, bool paused = false);
	virtual void removeAction(std::shared_ptr<FAction>& action);
	virtual void removeActionsByTarget(UActionComponent* target);
	virtual void removeAllActions();
	virtual void removeActionsByTag(int32 tag, UActionComponent* target);
	virtual void removeActionsByFlags(int32 flags, UActionComponent* target);

	virtual std::shared_ptr<FAction> getActionByTag(int32 tag, UActionComponent* target) const;

	virtual void 	pauseTarget(UActionComponent* target);	
	virtual void 	resumeTarget(UActionComponent* target);

	virtual void 	pauseAllActions();
	virtual void 	resumeAllActions();

	virtual void 	update(float dt);

private:
	typedef std::function<bool (const std::shared_ptr<FAction>& a)> RemoveChecker;
	void	_removeActions(ActionList& actions, ActionList* removed, const RemoveChecker& checker);
};
