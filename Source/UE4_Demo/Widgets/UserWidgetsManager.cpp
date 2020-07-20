// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgetsManager.h"
#include "UserWidgetPanel.h"
#include "ConstructorHelpers.h"

UUserWidgetPanel* UUserWidgetsManager::createWidget(const FString& path)
{
	UUserWidgetPanel* pPanel_ = nullptr;
	ConstructorHelpers::FObjectFinder<UUserWidgetPanel> finder(*path);
	if (finder.Succeeded())
	{
		pPanel_ = finder.Object;
		pPanel_->setPanelName(path);
		addWidget(path, pPanel_);
	}
	return pPanel_;
}

void UUserWidgetsManager::showWidget(const FString& path, uint8 showType, const FString& associatedName, bool create /*= true*/)
{
	UUserWidgetPanel* pPanel_ = findWidget(path);
	if (NULL == pPanel_ && create)
	{
		pPanel_ = createWidget(path);
	}

	if (nullptr != pPanel_)
	{
		if ( associatedName.IsEmpty() )
		{
			pPanel_->Show(showType);
		}
		else
		{
			pPanel_->ShowByAssociated(showType, associatedName);
		}
	}
}

void UUserWidgetsManager::hideWidget( const FString& path, uint8 hideType)
{
	UUserWidgetPanel* pPanel_ = findWidget(path);
	if ( NULL != pPanel_ )
	{
		pPanel_->Hide(hideType);
	}
}

bool UUserWidgetsManager::addWidget(const FString& path, UUserWidgetPanel* pWidgetPanel)
{
	m_widgets.Add(path, pWidgetPanel);
	return true;
}

void UUserWidgetsManager::removeWidget(const FString& path)
{
	m_widgets.Remove(path);
}

UUserWidgetPanel* UUserWidgetsManager::findWidget(const FString& path)
{
	UUserWidgetPanel** ppWidget = m_widgets.Find(path);
	if (nullptr != ppWidget)
	{
		return *ppWidget;
	}

	return NULL;
}

int32 UUserWidgetsManager::findWidgets(int32 catalog, TArray<UUserWidgetPanel*>& widgets)
{
	for ( auto itr = m_widgets.begin(); itr != m_widgets.end(); ++itr )
	{
		UUserWidgetPanel* pPanel_ = itr->Value;
		if (pPanel_->getCatalog() == catalog)
		{
			widgets.Add(pPanel_);
		}
	}
	return widgets.Num();
}