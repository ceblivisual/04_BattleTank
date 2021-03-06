// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Runtime/Core/Public/Math/Vector2D.h"

// Forward Decleration
class ATank;
class UTankAimingComponent;

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) {return;}
	FoundAimingComponent(AimingComponent);
}

void  ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) 
	{ 
		return; 
	} // e.g. if not possessing
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation; // Out parameter
	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
	if (bGotHitLocation) // Has "side-effect", is going to line trace
	{
		AimingComponent->AimAt(HitLocation);
	}
}

// Get World location if linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& Hitlocation) const
{
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	// "De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-Trace along that look direction, and see what we hit (up to max range)
		return GetLookVectorHitLocation(LookDirection, Hitlocation);
	}
	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult, 
		StartLocation, 
		EndLocation,	
		ECollisionChannel::ECC_Visibility)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}

	HitLocation = FVector(0);
	
	return false; // LineTrace didn't succeed

}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{	
	FVector CameraWorldLocation; // Not to be used
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection);
}

