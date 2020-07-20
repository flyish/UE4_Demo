// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTester.h"
#include "../Helper/HelperBlueprintFunctionLibrary.h"

// Sets default values
ABaseTester::ABaseTester()
	: m_nMaxStep( 0 )
	, m_nCurStep(0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseTester::BeginPlay()
{
	Super::BeginPlay();
	m_nCurStep = 1;
}

// Called every frame
void ABaseTester::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseTester::prevStep_Implementation()
{
	--m_nCurStep;
	if (m_nCurStep <= 0 )
	{
		UTesterController* pController_ = UHelperBlueprintFunctionLibrary::testerController();
		pController_->endTest();
	}
	else
	{
		onPrevStep();
	}
}

void ABaseTester::nextStep_Implementation()
{
	++m_nCurStep;
	if (m_nCurStep > m_nMaxStep)
	{
		UTesterController* pController_ = UHelperBlueprintFunctionLibrary::testerController();
		pController_->endTest();
	}
	else
	{
		onPrevStep();
	}
}

void ABaseTester::onPrevStep()
{

}

void ABaseTester::onNextStep()
{

}