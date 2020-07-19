// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <unordered_map>
#include <set>

class FAction;
class IActionNode;

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

	virtual void addAction(const std::shared_ptr<FAction>& action, IActionNode* target, bool paused = false);
	virtual void removeAction(const std::shared_ptr<FAction>& action);
	virtual void removeActionsByTarget(IActionNode* target);
	virtual void removeAllActions();
	virtual void removeActionsByTag(int32 tag, IActionNode* target);
	virtual void removeActionsByFlags(int32 flags, IActionNode* target);

	virtual std::shared_ptr<FAction> getActionByTag(int32 tag, IActionNode* target) const;

	virtual void	pauseAction(const std::shared_ptr<FAction>& action);
	virtual void	resumeAction(const std::shared_ptr<FAction>& action);

	virtual void 	pauseTarget(IActionNode* target);	
	virtual void 	resumeTarget(IActionNode* target);

	virtual void 	pauseAllActions();
	virtual void 	resumeAllActions();

	virtual void 	update(float dt);

private:
	typedef std::function<bool (const std::shared_ptr<FAction>& a)> RemoveChecker;
	void	_removeActions(ActionList& actions, ActionList* removed, const RemoveChecker& checker);
};
