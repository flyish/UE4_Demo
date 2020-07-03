// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraDirector.h"
#include "UObject/UObjectGlobals.h"
#include "Helper/HelperBlueprintFunctionLibrary.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

// Sets default values
ACameraDirector::ACameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();	

	UWorld* pWorld_ = GetWorld();
	if (nullptr == cameraActorOne)
	{
		cameraActorOne = FindObject<AActor>(pWorld_->GetCurrentLevel(), TEXT("CameraActorOne") );
	}
	if (nullptr == cameraActorTwo)
	{
		cameraActorTwo = FindObject<AActor>(pWorld_->GetCurrentLevel(), TEXT("CameraActorTwo"));
	}

	APlayerController* pc = UHelperBlueprintFunctionLibrary::GetFirstPlayerController(this);
	pc->SetViewTarget(cameraActorOne);

	pc->InputComponent->BindAction("CameraSwitch", IE_Pressed, this, &::ACameraDirector::SwitchCamera);
}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACameraDirector::SwitchCamera()
{
	APlayerController* pc = UHelperBlueprintFunctionLibrary::GetFirstPlayerController(this);
	
	if (pc->GetViewTarget() == cameraActorOne)
	{
		pc->SetViewTarget(cameraActorTwo);
	}
	else
	{
		pc->SetViewTarget(cameraActorOne);
	}
}

