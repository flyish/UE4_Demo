// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4_DemoGameModeBase.h"


AUE4_DemoGameModeBase::AUE4_DemoGameModeBase()
	: m_pActionManager( nullptr )
	, m_pUserWidgetManager( nullptr )
{

}


AUE4_DemoGameModeBase::~AUE4_DemoGameModeBase()
{
	if (NULL != m_pActionManager)
	{
		delete m_pActionManager;
		m_pActionManager = nullptr;
	}
	m_pUserWidgetManager = nullptr;
}

void AUE4_DemoGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	m_pActionManager = new FActionManager();
	m_pUserWidgetManager = NewObject<UUserWidgetsManager>();
}

void AUE4_DemoGameModeBase::StartPlay()
{
	Super::StartPlay();
}

FActionManager* AUE4_DemoGameModeBase::actionManager()
{
	return m_pActionManager;
}

UUserWidgetsManager* AUE4_DemoGameModeBase::userWidgetsManager()
{
	return m_pUserWidgetManager;
}
