// Fill out your copyright notice in the Description page of Project Settings.
#include "ConstructorHelpers.h"


#include "TesterController.h"
#include "../Widgets/UserWidgetsManager.h"
#include "../Helper/WidgetBlueprintFunctionLibrary.h"
#include "UMG/Public/Blueprint/UserWidget.h"
#include "../Helper/HelperBlueprintFunctionLibrary.h"
#include "ConstructorHelpers.h"
#include "Kismet/KismetSystemLibrary.h"

UTesterController::UTesterController()
	: m_pCurTester( nullptr )
{

}

UTesterController::~UTesterController()
{

}

bool UTesterController::initalize()
{
	UUserWidgetsManager* pWidgetManager_ = UWidgetBlueprintFunctionLibrary::widgetsManager();
	if (MenuPanelType.Get() != nullptr)
	{
		m_pMenuPanel = Cast<UMenuPanel>(CreateWidget(UHelperBlueprintFunctionLibrary::GetFirstPlayerController(this), MenuPanelType));
		m_pMenuPanel->setPanelName(TEXT("MenuPanel"));
		pWidgetManager_->addWidget(TEXT("DescPanel"), m_pMenuPanel);
	}
	else
	{
		m_pMenuPanel = Cast<UMenuPanel>(pWidgetManager_->createWidget(FString("")));
	}
	
	if (DescPanelType.Get() != nullptr)
	{
		m_pDescPanel = Cast<UDescPanel>( CreateWidget(UHelperBlueprintFunctionLibrary::GetFirstPlayerController(this), DescPanelType) );
		m_pDescPanel->setPanelName(TEXT("DescPanel"));

		pWidgetManager_->addWidget(TEXT("DescPanel"), m_pDescPanel);
	}
	else
	{
		m_pDescPanel = Cast<UDescPanel>(pWidgetManager_->createWidget(FString("")));
	}

	return true;
}

void UTesterController::finilise()
{
	UUserWidgetsManager* pWidgetManager_ = UWidgetBlueprintFunctionLibrary::widgetsManager();
	if (nullptr != m_pDescPanel)
	{
		pWidgetManager_->removeWidget( m_pDescPanel->getPanelName() );
	}

	if (nullptr != m_pMenuPanel)
	{
		pWidgetManager_->removeWidget(m_pMenuPanel->getPanelName());
	}
}

void UTesterController::startTest(const FString& path)
{
	if (nullptr != m_pCurTester)
	{
		m_pCurTester->Destroy();
		m_pCurTester = nullptr;
	}

	ConstructorHelpers::FObjectFinder<ABaseTester> finder(*path);
	if (finder.Succeeded())
	{
		m_pCurTester = finder.Object;
	}
	else
	{
		UKismetSystemLibrary::PrintString(this, path + TEXT(" not found!!!!"));
		endTest();
	}
}

void UTesterController::endTest()
{
	m_pDescPanel->Hide((uint8)EPanelHideType::E_PANEL_HIDE_NORMAL);
	m_pMenuPanel->Show((uint8)EPanelShowType::E_PANEL_SHOW_NORMAL);
}

void UTesterController::setTestDesc(int32 step, int32 maxstep, const FString& desc)
{
	if (nullptr != m_pDescPanel)
	{
		m_pDescPanel->setTestDesc(step, maxstep, desc);
	}
}

void UTesterController::nextStep()
{
	if (nullptr != m_pCurTester)
	{
		m_pCurTester->nextStep();
	}
	else
	{
		endTest();
	}
}

void UTesterController::prevStep()
{
	if (nullptr != m_pCurTester)
	{
		m_pCurTester->prevStep();
	}
	else
	{
		endTest();
	}
}
