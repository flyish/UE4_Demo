// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgetsManager.h"
#include "UserWidgetPanel.h"
#include "ConstructorHelpers.h"

void UUserWidgetsManager::showWidget(const FName& path, uint8 showType, const FName& associatedName, bool create /*= true*/)
{
	UUserWidgetPanel* pPanel_ = findWidget(path);
	if (NULL == pPanel_ && create)
	{
		const FString& s = path.ToString();
		ConstructorHelpers::FObjectFinder<UUserWidgetPanel> finder( *s );
		if (finder.Succeeded())
		{
			pPanel_ = finder.Object;
			pPanel_->setPanelName(path);
		}
	}

	if (nullptr != pPanel_)
	{
		if (associatedName.IsNone())
		{
			pPanel_->Show(showType);
		}
		else
		{
			pPanel_->ShowByAssociated(showType, associatedName);
		}
	}
}

void UUserWidgetsManager::hideWidget( const FName& path, uint8 hideType)
{
	UUserWidgetPanel* pPanel_ = findWidget(path);
	if ( NULL != pPanel_ )
	{
		pPanel_->Hide(hideType);
	}
}

void UUserWidgetsManager::removeWidget(const FName& path)
{
	m_widgets.Remove(path);
}

UUserWidgetPanel* UUserWidgetsManager::findWidget(const FName& path)
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