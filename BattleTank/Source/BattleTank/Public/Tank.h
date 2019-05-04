// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // Put new include above

// Forward declarations
class UTankBarrel;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Fire();

	virtual void BeginPlay() override;

private:
	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY(EditAnywhere, category = "Firing")
	float LaunchSpeed = 5000;
	
	UPROPERTY(EditAnywhere, category = "Setup")
	TSubclassOf<AProjectile> ProjectileBluePrint;
	
	UPROPERTY(EditDefaultsOnly, category = "Firing")
	float ReloadTimeInSeconds = 2;

	// Local barel reference for spawning projectile
	UTankBarrel* Barrel = nullptr; // TODO remove

	double LastFireTime = 0;
};
