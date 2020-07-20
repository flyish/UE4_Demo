// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4_DemoGameModeBase.h"


AUE4_DemoGameModeBase::AUE4_DemoGameModeBase()
	: m_pActionManager( nullptr )
	, m_pUserWidgetManager( nullptr )
	, m_pTesterController( nullptr )
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
	m_pTesterController = nullptr;
}

void AUE4_DemoGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	m_pActionManager = new FActionManager();
	if (nullptr == m_pUserWidgetManager)
	{
		m_pUserWidgetManager = NewObject<UUserWidgetsManager>();
	}

	if (nullptr == m_pTesterController)
	{
		m_pTesterController = NewObject<UTesterController>();
	}
}

void AUE4_DemoGameModeBase::StartPlay()
{
	Super::StartPlay();

	if (nullptr != m_pTesterController)
	{
		m_pTesterController->initalize();
	}
}


void AUE4_DemoGameModeBase::BeginDestroy()
{
	Super::BeginDestroy();

	if (nullptr != m_pTesterController)
	{
		m_pTesterController->finilise();
	}
}

FActionManager* AUE4_DemoGameModeBase::actionManager()
{
	return m_pActionManager;
}

UUserWidgetsManager* AUE4_DemoGameModeBase::userWidgetsManager()
{
	return m_pUserWidgetManager;
}

UTesterController* AUE4_DemoGameModeBase::testerController()
{
	return m_pTesterController;
}
