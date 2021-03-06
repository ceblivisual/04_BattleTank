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
	Locked,
	OutOfAmmo
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
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int32 GetRoundLeft() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState Firingstate = EFiringState::Reloading;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	
	void MoveBarrelTowards(FVector AimDirection);

	UPROPERTY(EditAnywhere, category = "Setup")
	TSubclassOf<AProjectile> ProjectileBluePrint;


	UPROPERTY(EditDefaultsOnly, category = "Firing")
	float ReloadTimeInSeconds = 2;

	UPROPERTY(EditAnywhere, category = "Firing")
	int32 RoundLeft = 3;

	UPROPERTY(EditAnywhere, category = "Firing")
	float LaunchSpeed = 4000;

	FVector AimDirection;

	bool IsBarrelMoving();

	double LastFireTime = 0;
};


