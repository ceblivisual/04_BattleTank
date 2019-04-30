// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force, and to apply forces to the tank
 */
UCLASS(meta = (BlueprintSpawnableComponent)) //, hidecategories = ("Collision"))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
		// Sets a throtle between -1 and 1
public:
		UFUNCTION(BlueprintCallable, Category = "Input")
		void SetThrotle(float Throtle);

	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 200000; // Assume 30 tonne tank, 1g acceleration
};