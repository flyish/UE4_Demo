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

void FActionManager::addAction(TSharedPtr<FAction, ESPMode::NotThreadSafe>& action, bool paused)
{
	if (paused)
	{
		m_pausedList.insert(action);
	}
	else
	{
		m_runActions.insert(action);
	}
}

void FActionManager::removeAction(TSharedPtr<FAction, ESPMode::NotThreadSafe>& action)
{
	m_runActions.erase(action);
	m_pausedList.erase(action);
}

void FActionManager::removeActionsByTarget(UActionComponent* target)
{
	m_runActions.erase(std::remove_if(m_runActions.begin(), m_runActions.end(), [&](const TSharedPtr<FAction, ESPMode::NotThreadSafe>& a) {
			return a->getTarget() == target;
		}), m_runActions.end());

	m_pausedList.erase(std::remove_if(m_pausedList.begin(), m_pausedList.end(), [&](const TSharedPtr<FAction, ESPMode::NotThreadSafe>& a) {
		return a->getTarget() == target;
		}), m_pausedList.end());
}

void FActionManager::removeAllActions()
{
	m_runActions.clear();
	m_pausedList.clear();
}

void FActionManager::removeActionsByTag(int32 tag, UActionComponent* target)
{
	m_runActions.erase(std::remove_if(m_runActions.begin(), m_runActions.end(), [&](const TSharedPtr<FAction, ESPMode::NotThreadSafe>& a) {
		return a->getTarget() == target && a->getTag() == tag;
		}), m_runActions.end());

	m_pausedList.erase(std::remove_if(m_pausedList.begin(), m_pausedList.end(), [&](const TSharedPtr<FAction, ESPMode::NotThreadSafe>& a) {
		return a->getTarget() == target && a->getTag() == tag;
		}), m_pausedList.end());
}

void FActionManager::removeActionsByFlags(int32 flags, UActionComponent* target)
{
	m_runActions.erase(std::remove_if(m_runActions.begin(), m_runActions.end(), [&](const TSharedPtr<FAction, ESPMode::NotThreadSafe>& a) {
		return a->getTarget() == target && a->getFlags() == flags;
		}), m_runActions.end());

	m_pausedList.erase(std::remove_if(m_pausedList.begin(), m_pausedList.end(), [&](const TSharedPtr<FAction, ESPMode::NotThreadSafe>& a) {
		return a->getTarget() == target && a->getFlags() == flags;
		}), m_pausedList.end());
}

TSharedPtr<FAction, ESPMode::NotThreadSafe> FActionManager::getActionByTag(int32 tag, UActionComponent* target) const
{
	for (ActionList::iterator itr_ = m_runActions.begin(); itr_ != m_runActions.end(); ++itr_)
	{
		const TSharedPtr<FAction, ESPMode::NotThreadSafe>& a_ = *itr_;
		if (a_->getTag() == tag && a_->getTarget() == target )
		{
			return a_;
		}
	}
	
	return TSharedPtr<FAction, ESPMode::NotThreadSafe>();
}

void FActionManager::pauseTarget(UActionComponent* target)
{
	ActionList::iterator itr_ = std::remove_if(m_runActions.begin(), m_runActions.end(), [&](const TSharedPtr<FAction, ESPMode::NotThreadSafe>& a) {
			return a->getTarget() == target;
		});

	m_pausedList.insert(itr_, m_runActions.end());
	m_runActions.erase(itr_, m_runActions.end());
}

void FActionManager::resumeTarget(UActionComponent* target)
{
	ActionList::iterator itr_ = std::remove_if(m_pausedList.begin(), m_pausedList.end(), [&](const TSharedPtr<FAction, ESPMode::NotThreadSafe>& a) {
		return a->getTarget() == target;
		});

	m_runActions.insert(itr_, m_pausedList.end());
	m_pausedList.erase(itr_, m_pausedList.end());
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
		const TSharedPtr<FAction, ESPMode::NotThreadSafe>& a_ = *itr_;

		a_->step( dt );
		if (a_->isDone())
		{
			m_runActions.erase(itr_);
		}
	}
}
