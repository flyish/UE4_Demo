// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../UE4_DemoGameModeBase.h"

// Sets default values for this component's properties
UActionComponent::UActionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UActionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FVector UActionComponent::getLocation() const
{
	AActor* pOwner_ = GetOwner();
	if (nullptr != pOwner_ )
	{
		return pOwner_->GetActorLocation();
	}

	return FVector();
}

void UActionComponent::setLocation(const FVector& location)
{
	AActor* pOwner_ = GetOwner();
	if (nullptr != pOwner_)
	{
		pOwner_->SetActorLocation( location );
	}
}

void UActionComponent::runAction(std::shared_ptr<FAction>& action)
{
	AUE4_DemoGameModeBase* pGameBase_ = Cast<AUE4_DemoGameModeBase>(	 UGameplayStatics::GetGameMode(this->GetOwner()) );
	verify(pGameBase_);

	FActionManager* pActionManager_ = pGameBase_->actionManager();
	if (nullptr != pActionManager_)
	{
		pActionManager_->addAction(action, this);
	}
}

void UActionComponent::runAction(UActionWraper* action)
{
	if (NULL != action)
	{
		runAction(action->realAction());
	}
}

void UActionComponent::stopAction(std::shared_ptr<FAction>& action)
{
	//check(action->getTag() == this);

	AUE4_DemoGameModeBase* pGameBase_ = Cast<AUE4_DemoGameModeBase>(UGameplayStatics::GetGameMode(this->GetOwner()));
	verify(pGameBase_);

	FActionManager* pActionManager_ = pGameBase_->actionManager();
	if (nullptr != pActionManager_)
	{
		pActionManager_->removeAction(action);
	}
}

void UActionComponent::stopAction(UActionWraper* action)
{
	if (NULL != action)
	{
		stopAction(action->realAction());
	}
}

void UActionComponent::stopAllActions()
{
	AUE4_DemoGameModeBase* pGameBase_ = Cast<AUE4_DemoGameModeBase>(UGameplayStatics::GetGameMode(this->GetOwner()));
	verify(pGameBase_);

	FActionManager* pActionManager_ = pGameBase_->actionManager();
	if (nullptr != pActionManager_)
	{
		pActionManager_->removeActionsByTarget(this);
	}
}

void UActionComponent::pauseAction(std::shared_ptr<FAction>& action)
{
	AUE4_DemoGameModeBase* pGameBase_ = Cast<AUE4_DemoGameModeBase>(UGameplayStatics::GetGameMode(this->GetOwner()));
	verify(pGameBase_);

	FActionManager* pActionManager_ = pGameBase_->actionManager();
	if (nullptr != pActionManager_)
	{
		pActionManager_->pauseAction(action);
	}
}

void UActionComponent::pauseAction(UActionWraper* action)
{
	if (NULL != action)
	{
		pauseAction(action->realAction());
	}
}

void UActionComponent::pauseAllActions()
{
	AUE4_DemoGameModeBase* pGameBase_ = Cast<AUE4_DemoGameModeBase>(UGameplayStatics::GetGameMode(this->GetOwner()));
	verify(pGameBase_);

	FActionManager* pActionManager_ = pGameBase_->actionManager();
	if (nullptr != pActionManager_)
	{
		pActionManager_->pauseTarget(this);
	}
}

void UActionComponent::resumeAction(std::shared_ptr<FAction>& action)
{
	AUE4_DemoGameModeBase* pGameBase_ = Cast<AUE4_DemoGameModeBase>(UGameplayStatics::GetGameMode(this->GetOwner()));
	verify(pGameBase_);

	FActionManager* pActionManager_ = pGameBase_->actionManager();
	if (nullptr != pActionManager_)
	{
		pActionManager_->resumeAction(action);
	}
}

void UActionComponent::resumeAction(UActionWraper* action)
{
	if (NULL != action)
	{
		resumeAction(action->realAction());
	}
}

void UActionComponent::resumeAllActions()
{
	AUE4_DemoGameModeBase* pGameBase_ = Cast<AUE4_DemoGameModeBase>(UGameplayStatics::GetGameMode(this->GetOwner()));
	verify(pGameBase_);

	FActionManager* pActionManager_ = pGameBase_->actionManager();
	if (nullptr != pActionManager_)
	{
		pActionManager_->resumeTarget(this);
	}
}

