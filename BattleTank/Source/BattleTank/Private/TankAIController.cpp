// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	auto ControlledTank = GetPawn();
	
	// Aim towards the player
	if (!ensure(ControlledTank)) { return; }
	if (!ensure(PlayerTank)) { return; }
	// Move towards the player
		MoveToActor(PlayerTank, AcceptenceRadius);
		auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();

		AimingComponent->AimAt(PlayerTank->GetActorLocation());

		// TODO Fix firing
		AimingComponent->Fire();
}

