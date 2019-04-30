// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
class UTankBarrel;

UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = "Setup")
		float MaxDegreesPerSecond = 20; // Sensible default
	UPROPERTY(EditAnywhere, Category = "Setup")
		float MaxElevation = 40; // Sensible default
	UPROPERTY(EditAnywhere, Category = "Setup")
		float MinElevation = 0; // Sensible default
	
};
