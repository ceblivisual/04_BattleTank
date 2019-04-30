// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Projectile.h"
#include "Components/InputComponent.h"
#include "BattleTank.h"
#include "TankBarrel.h"
#include "GameFramework/DefaultPawn.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// No need to protect points as added at construction
	//TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (Barrel && isReloaded){

		//spawn a projectile at the socket location on the barel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBluePrint,
		Barrel->GetSocketLocation(FName("Projectile")),
		Barrel->GetSocketRotation(FName("Projectile"))		
		);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}
