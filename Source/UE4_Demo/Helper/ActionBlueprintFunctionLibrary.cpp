// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionBlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "../UE4_DemoGameModeBase.h"

void UActionBlueprintFunctionLibrary::stopAllActions()
{
	AUE4_DemoGameModeBase* pGameBase_ = Cast<AUE4_DemoGameModeBase>( GEngine->GetWorld()->GetAuthGameMode() );
	verify(pGameBase_);

	FActionManager* pActionManager_ = pGameBase_->actionManager();
	if (nullptr != pActionManager_)
	{
		pActionManager_->removeAllActions();
	}
}

void UActionBlueprintFunctionLibrary::pauseAllActions()
{
	AUE4_DemoGameModeBase* pGameBase_ = Cast<AUE4_DemoGameModeBase>(GEngine->GetWorld()->GetAuthGameMode());
	verify(pGameBase_);

	FActionManager* pActionManager_ = pGameBase_->actionManager();
	if (nullptr != pActionManager_)
	{
		pActionManager_->pauseAllActions();
	}
}

void UActionBlueprintFunctionLibrary::resumeAllActions()
{
	AUE4_DemoGameModeBase* pGameBase_ = Cast<AUE4_DemoGameModeBase>(GEngine->GetWorld()->GetAuthGameMode());
	verify(pGameBase_);

	FActionManager* pActionManager_ = pGameBase_->actionManager();
	if (nullptr != pActionManager_)
	{
		pActionManager_->resumeAllActions();
	}
}
