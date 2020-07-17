// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionManager.h"
#include "ActionComponent.h"
#include "Action.h"

FActionManager::FActionManager()
{
}

FActionManager::~FActionManager()
{
	m_runActions.clear();
	m_pausedList.clear();
}

void FActionManager::addAction(std::shared_ptr<FAction>& action, UActionComponent* target, bool paused)
{
	action->startWithTarget(target);

	if (paused)
	{
		m_pausedList.insert(action);
	}
	else
	{
		m_runActions.insert(action);
	}
}

void FActionManager::removeAction(std::shared_ptr<FAction>& action)
{
	m_runActions.erase(action);
	m_pausedList.erase(action);
}

void FActionManager::removeActionsByTarget(UActionComponent* target)
{
	RemoveChecker pf = [&](const std::shared_ptr<FAction>& a)->bool {
		return a->getTarget() == target;
	};
	_removeActions(m_runActions, nullptr, pf);
	_removeActions(m_pausedList, nullptr, pf);
}

void FActionManager::removeAllActions()
{
	m_runActions.clear();
	m_pausedList.clear();
}

void FActionManager::removeActionsByTag(int32 tag, UActionComponent* target)
{
	RemoveChecker pf = [&](const std::shared_ptr<FAction>& a)->bool {
		return a->getTarget() == target && a->getTag() == tag;
	};
	_removeActions(m_runActions, nullptr, pf);
	_removeActions(m_pausedList, nullptr, pf);
}

void FActionManager::removeActionsByFlags(int32 flags, UActionComponent* target)
{
	RemoveChecker pf = [&](const std::shared_ptr<FAction>& a)->bool {
		return a->getTarget() == target && a->getFlags() == flags;
	};
	_removeActions(m_runActions, nullptr, pf);
	_removeActions(m_pausedList, nullptr, pf);
}

std::shared_ptr<FAction> FActionManager::getActionByTag(int32 tag, UActionComponent* target) const
{
	for (ActionList::iterator itr_ = m_runActions.begin(); itr_ != m_runActions.end(); ++itr_)
	{
		const std::shared_ptr<FAction>& a_ = *itr_;
		if (a_->getTag() == tag && a_->getTarget() == target )
		{
			return a_;
		}
	}
	
	return std::shared_ptr<FAction>();
}


void FActionManager::pauseAction(std::shared_ptr<FAction>& action)
{
	ActionList::iterator itr_ = m_runActions.find(action);
	if (itr_ != m_runActions.end())
	{
		m_runActions.erase(itr_);
		m_pausedList.insert(action);
	}
}


void FActionManager::resumeAction(std::shared_ptr<FAction>& action)
{
	ActionList::iterator itr_ = m_pausedList.find(action);
	if (itr_ != m_pausedList.end())
	{
		m_pausedList.erase(itr_);
		m_runActions.insert(action);
	}
}

void FActionManager::pauseTarget(UActionComponent* target)
{
	RemoveChecker pf = [&](const std::shared_ptr<FAction>& a)->bool {
		return a->getTarget() == target;
	};
	ActionList removed;
	_removeActions(m_runActions, &removed, pf);

	m_pausedList.insert(removed.begin(), removed.end());
}

void FActionManager::resumeTarget(UActionComponent* target)
{
	RemoveChecker pf = [&](const std::shared_ptr<FAction>& a)->bool {
		return a->getTarget() == target;
	};
	ActionList removed;
	_removeActions(m_pausedList, &removed, pf);

	m_runActions.insert(removed.begin(), removed.end());
}

void FActionManager::pauseAllActions()
{
	m_pausedList.insert(m_runActions.begin(), m_runActions.end());

	m_runActions.clear();
}

void FActionManager::resumeAllActions()
{
	m_runActions.insert(m_pausedList.begin(), m_pausedList.end());

	m_pausedList.clear();
}

void FActionManager::update(float dt)
{
	for (ActionList::iterator itr_ = m_runActions.begin(), next_ = itr_; itr_ != m_runActions.end(); itr_ = next_)
	{
		++next_;
		const std::shared_ptr<FAction>& a_ = *itr_;

		a_->step( dt );
		if (a_->isDone())
		{
			m_runActions.erase(itr_);
		}
	}
}

void FActionManager::_removeActions(ActionList& actions, ActionList* removed, const RemoveChecker& checker)
{
	if (nullptr == removed)
	{
		for (ActionList::iterator itr_ = actions.begin(), next_ = itr_; itr_ != actions.end(); itr_ = next_)
		{
			++next_;
			const std::shared_ptr<FAction>& a_ = *itr_;

			if (checker(a_))
			{
				actions.erase(itr_);
			}
		}
	}
	else
	{
		for (ActionList::iterator itr_ = actions.begin(), next_ = itr_; itr_ != actions.end(); itr_ = next_)
		{
			++next_;
			const std::shared_ptr<FAction>& a_ = *itr_;

			if (checker(a_))
			{
				removed->insert(a_);

				actions.erase(itr_);
			}
		}
	}
}
