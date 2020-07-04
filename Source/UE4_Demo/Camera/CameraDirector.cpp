// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraDirector.h"
#include "UObject/UObjectGlobals.h"
#include "Helper/HelperBlueprintFunctionLibrary.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ACameraDirector::ACameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	rotateSpeed = 180;
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

	pc->InputComponent->BindAction("CameraSwitch", IE_Pressed, this, &ACameraDirector::SwitchCamera);
	pc->InputComponent->BindAxis("CameraRotate", this, &ACameraDirector::RotateCamera);
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
		pc->SetViewTargetWithBlend( cameraActorTwo, 1.0f );
	}
	else
	{
		pc->SetViewTargetWithBlend( cameraActorOne, 1.0f );
	}
}

void ACameraDirector::RotateCamera(float delta)
{
	if (delta < 0.5 && delta > -0.5)
	{
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("rotate delta:%f"), delta);
	FVector baseLocation(0, 0 ,0);
	// get default character
	APawn* pMainPawn = UHelperBlueprintFunctionLibrary::GetFirstPlayerPawn(this);
	if (NULL != pMainPawn)
	{
		baseLocation = pMainPawn->GetActorLocation();
	}

	APlayerController* pc = UHelperBlueprintFunctionLibrary::GetFirstPlayerController(this);
	AActor* cameraActor = pc->GetViewTarget();

	float angle = delta * rotateSpeed * GetWorld()->DeltaTimeSeconds;
	//FRotator NewRotation = FRotator(0, angle, 0);
	//FQuat QuatRotation = FQuat(NewRotation);
	//cameraActor->AddActorWorldRotation(QuatRotation);

	FVector cameraLocation = cameraActor->GetActorLocation();
	FVector dir = cameraLocation - baseLocation;  
	dir = dir.RotateAngleAxis(angle, FVector(0, 0, 1));
	FVector newLocation = baseLocation + dir;
	cameraActor->SetActorLocation(newLocation);

	// draw a line
	UWorld* pWorld_ = GetWorld();
	DrawDebugLine(pWorld_, newLocation, baseLocation, FColor(255, 0, 0), false, 1, 0, 10);

	// set camera forward to base actor
	FRotator newRotator = UKismetMathLibrary::FindLookAtRotation(newLocation, baseLocation);
	cameraActor->SetActorRotation(newRotator, ETeleportType::TeleportPhysics);
}

