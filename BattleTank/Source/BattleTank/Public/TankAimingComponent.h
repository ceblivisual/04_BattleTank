// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

// Forward Decleration
class UTankBarrel;
class UTankTurret;
class AProjectile;

// Holds barrels properties and elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
	
	UPROPERTY(EditAnywhere, category = "Firing")
	float LaunchSpeed = 4000;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Fire();

	bool IsBarrelMoving();



protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState Firingstate = EFiringState::Locked;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	
	void MoveBarrelTowards(FVector AimDirection);
	void MoveTurretTowards(FVector AimDirection);

	UPROPERTY(EditAnywhere, category = "Setup")
	TSubclassOf<AProjectile> ProjectileBluePrint;

	double LastFireTime = 0;

	UPROPERTY(EditDefaultsOnly, category = "Firing")
	float ReloadTimeInSeconds = 2;

	FVector AimDirection;
};


