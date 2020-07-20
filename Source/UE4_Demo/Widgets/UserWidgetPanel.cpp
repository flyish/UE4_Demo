// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgetPanel.h"
#include "../UE4_DemoGameModeBase.h"
#include "../Helper/WidgetBlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "../Action/ParallelAction.h"
#include "../Action/SequenceAction.h"
#include <memory>
#include "../Action/CallBackAction.h"
#include "../Action/MoveToAction.h"
#include "../Action/ScaleAction.h"

void UUserWidgetPanel::PostLoad()
{
	Super::PostLoad();

	onPostLoad();
}

void UUserWidgetPanel::FinishDestroy()
{
	onDestory();

	Super::FinishDestroy();
}

void UUserWidgetPanel::onPostLoad_Implementation()
{

}

void UUserWidgetPanel::onDestory_Implementation()
{

}

void UUserWidgetPanel::Show_Implementation(uint8 showType)
{
	InnerShow(showType, FString());
}


void UUserWidgetPanel::ShowByAssociated_Implementation(uint8 showType, const FString& associatedName)
{
	InnerShow(showType, associatedName);
}

void UUserWidgetPanel::Hide_Implementation(uint8 hideType)
{
	m_bIsShowed = false;
	
	if (EPanelHideType(hideType) == EPanelHideType::E_PANEL_HIDE_PUSH)
	{
		m_showPoint = FVector2D( getLocation() );
	}

	// show self action; 
	FParallelAction* paralleAction_ = new FParallelAction();
	FMoveToAction* moveAction_ = new FMoveToAction(FVector(m_initPoint, m_zOrder));
	FScaleAction* scaleAction_ = new FScaleAction(FVector(m_initScale, 1.0f ));
	paralleAction_->addAction( moveAction_->shared_from_this() );
	paralleAction_->addAction( scaleAction_->shared_from_this() );

	FSequenceAction* sequenceAction_ = new FSequenceAction();
	sequenceAction_->addAction( paralleAction_->shared_from_this() );

	FActionDelegateEx callback_ = FActionDelegateEx::CreateUObject(this, &UUserWidgetPanel::onFinishHide);
	FCallbackActionEx* callbackAction_ = new FCallbackActionEx(callback_, (void*)hideType);
	sequenceAction_->addAction( callbackAction_->shared_from_this());
	this->runAction(sequenceAction_->shared_from_this());
}

void UUserWidgetPanel::InnerShow(uint8 showType, const FString& associatedName)
{
	if (EPanelShowType(showType) != EPanelShowType::E_PANEL_SHOW_RESTORE)
	{
		m_showType = showType;
		if (m_associatedName != associatedName)
		{
			m_associatedName = associatedName;
		}

		if (EPanelShowType(showType) != EPanelShowType::E_PANEL_SHOW_NORMAL)
		{
			UUserWidgetsManager* widgetsManager_ = UWidgetBlueprintFunctionLibrary::widgetsManager();
			TArray<UUserWidgetPanel*> assoicateds;
			if (m_associatedName.IsEmpty())
			{
				UUserWidgetPanel* pAssoicatedPanel_ = widgetsManager_->findWidget(m_associatedName);
				if (nullptr != pAssoicatedPanel_)
				{
					assoicateds.Add(pAssoicatedPanel_);
				}
			}
			else
			{
				widgetsManager_->findWidgets(m_panelGroup, assoicateds);
			}

			switch (EPanelShowType(showType))
			{
			// TODO: handler append, reposition all panel
			case EPanelShowType::E_PANEL_SHOW_APPEND:
			case EPanelShowType::E_PANEL_SHOW_PUSH:
				for ( auto w : assoicateds )
				{
					w->Hide((uint8)EPanelHideType::E_PANEL_HIDE_PUSH);
				}
				break;
			case EPanelShowType::E_PANEL_SHOW_REPLACE:
				for (auto w : assoicateds)
				{
					w->Hide((uint8)EPanelHideType::E_PANEL_HIDE_CLOSE);
				}
				break;
			default:
				break;
			}
		}
	}

	m_bIsShowed = true;
	AddToViewport(m_zOrder);
	this->setScale( FVector( m_initScale.X, m_initScale.Y, 1.0 ) );
	this->setLocation(FVector(m_initPoint.X, m_initPoint.Y, m_zOrder ) );

	// show self action; 
	FParallelAction* paralleAction_ = new FParallelAction();
	FMoveToAction* moveAction_ = new FMoveToAction(FVector(m_showPoint, m_zOrder));
	FScaleAction* scaleAction_ = new FScaleAction(FVector(1.0, 1.0, 1.0));
	paralleAction_->addAction(moveAction_->shared_from_this());
	paralleAction_->addAction(scaleAction_->shared_from_this());

	FSequenceAction* sequenceAction_ = new FSequenceAction();
	sequenceAction_->addAction(paralleAction_->shared_from_this());

	FActionDelegateEx callback_ = FActionDelegateEx::CreateUObject(this, &UUserWidgetPanel::onFinishShow);
	FCallbackActionEx* callbackAction_ = new FCallbackActionEx(callback_, (void*)showType);
	sequenceAction_->addAction(callbackAction_->shared_from_this());
	this->runAction( sequenceAction_->shared_from_this() );
}

void UUserWidgetPanel::onShow(uint8 showType)
{
	OnShowDelegate.ExecuteIfBound(this, showType);
}

void UUserWidgetPanel::onHide(uint8 hideType)
{
	OnShowDelegate.ExecuteIfBound(this, hideType);
}

void UUserWidgetPanel::onFinishShow(void* pContext)
{
	uint8 showType_ = (uint8)(size_t)pContext;
	onShow(showType_);
}

void UUserWidgetPanel::onFinishHide(void* pContext)
{
	uint8 hideType_ = (uint8)(size_t)pContext;
	onHide(hideType_);
	UUserWidgetsManager* widgetManager_ = UWidgetBlueprintFunctionLibrary::widgetsManager();
	if (hideType_ == (uint8)EPanelHideType::E_PANEL_HIDE_CLOSE)
	{
		widgetManager_->removeWidget(m_selFString);
	}
	RemoveFromViewport();
}

void UUserWidgetPanel::setPanelName(const FString& name)
{
	m_selFString = name;
}

const FString& UUserWidgetPanel::getAssociatedName() const
{
	return m_associatedName;
}

const FString& UUserWidgetPanel::getPanelName() const
{
	return m_selFString;
}

int32 UUserWidgetPanel::getCatalog() const
{
	return m_panelGroup;
}

uint8 UUserWidgetPanel::getShowType() const
{
	return m_showType;
}

bool UUserWidgetPanel::isShowed() const
{
	return m_bIsShowed;
}

FVector UUserWidgetPanel::getLocation() const
{
	FVector v = { RenderTransform.Translation.X, RenderTransform.Translation.Y, 0.0f};
	return v;
}

void UUserWidgetPanel::setLocation(const FVector& location)
{
	FVector2D v = { location.X, location.Y };
	this->SetRenderTranslation(v);
}

FVector UUserWidgetPanel::getScale() const
{
	FVector s = { RenderTransform.Scale.X, RenderTransform.Scale.Y, 1.0f };
	return s;
}

void UUserWidgetPanel::setScale(FVector s)
{
	FVector2D v = { s.X, s.Y };
	this->SetRenderScale(v);
}

void UUserWidgetPanel::runAction(const std::shared_ptr<FAction>& action)
{
	AUE4_DemoGameModeBase* pGameBase_ = Cast<AUE4_DemoGameModeBase>(UGameplayStatics::GetGameMode(this));
	verify(pGameBase_);

	FActionManager* pActionManager_ = pGameBase_->actionManager();
	if (nullptr != pActionManager_)
	{
		pActionManager_->addAction(action, this);
	}
}

void UUserWidgetPanel::runAction(UActionWraper* action)
{
	if (nullptr != action)
	{
		runAction(action->realAction());
	}
}

void UUserWidgetPanel::stopAction(const std::shared_ptr<FAction>& action)
{
	AUE4_DemoGameModeBase* pGameBase_ = Cast<AUE4_DemoGameModeBase>(UGameplayStatics::GetGameMode(this));
	verify(pGameBase_);

	FActionManager* pActionManager_ = pGameBase_->actionManager();
	if (nullptr != pActionManager_)
	{
		pActionManager_->removeAction(action);
	}
}

void UUserWidgetPanel::stopAction(UActionWraper* action)
{
	if (nullptr != action)
	{
		stopAction(action->realAction());
	}
}

void UUserWidgetPanel::stopAllActions()
{
	AUE4_DemoGameModeBase* pGameBase_ = Cast<AUE4_DemoGameModeBase>(UGameplayStatics::GetGameMode(this));
	verify(pGameBase_);

	FActionManager* pActionManager_ = pGameBase_->actionManager();
	if (nullptr != pActionManager_)
	{
		pActionManager_->removeActionsByTarget(this);
	}
}

void UUserWidgetPanel::pauseAction(const std::shared_ptr<FAction>& action)
{
	AUE4_DemoGameModeBase* pGameBase_ = Cast<AUE4_DemoGameModeBase>(UGameplayStatics::GetGameMode(this));
	verify(pGameBase_);

	FActionManager* pActionManager_ = pGameBase_->actionManager();
	if (nullptr != pActionManager_)
	{
		pActionManager_->pauseAction(action);
	}
}

void UUserWidgetPanel::pauseAction(UActionWraper* action)
{
	if (nullptr != action)
	{
		pauseAction(action->realAction());
	}
}

void UUserWidgetPanel::pauseAllActions()
{
	AUE4_DemoGameModeBase* pGameBase_ = Cast<AUE4_DemoGameModeBase>(UGameplayStatics::GetGameMode(this));
	verify(pGameBase_);

	FActionManager* pActionManager_ = pGameBase_->actionManager();
	if (nullptr != pActionManager_)
	{
		pActionManager_->pauseTarget(this);
	}
}

void UUserWidgetPanel::resumeAction(const std::shared_ptr<FAction>& action)
{
	AUE4_DemoGameModeBase* pGameBase_ = Cast<AUE4_DemoGameModeBase>(UGameplayStatics::GetGameMode(this));
	verify(pGameBase_);

	FActionManager* pActionManager_ = pGameBase_->actionManager();
	if (nullptr != pActionManager_)
	{
		pActionManager_->resumeAction(action);
	}
}

void UUserWidgetPanel::resumeAction(UActionWraper* action)
{
	if (nullptr != action)
	{
		resumeAction(action->realAction());
	}
}

void UUserWidgetPanel::resumeAllActions()
{
	AUE4_DemoGameModeBase* pGameBase_ = Cast<AUE4_DemoGameModeBase>(UGameplayStatics::GetGameMode(this));
	verify(pGameBase_);

	FActionManager* pActionManager_ = pGameBase_->actionManager();
	if (nullptr != pActionManager_)
	{
		pActionManager_->resumeTarget(this);
	}
}
