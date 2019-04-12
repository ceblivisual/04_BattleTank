// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "BattleTank.h"

void  ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s!"), *ControlledTank->GetName());
	}
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void  ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank())	{return;}

	FVector HitLocation; // Our parameter
	
	// Return an OUT Parameter, true if hit landscape 

	if (GetSightRayHitLocation(HitLocation))
	{	
	UE_LOG(LogTemp, Warning, TEXT("Hitlocation : %s"), *HitLocation.ToString())
	}
	// 
		// TODO Tell controlled tank to aim at this point
}

// Get World location if linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& Hitlocation) const
{
	Hitlocation = FVector(1.f);
	return true;
}
