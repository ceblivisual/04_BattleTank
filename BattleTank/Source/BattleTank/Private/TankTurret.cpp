// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
#include "Runtime/Renderer/Public/MeshDrawShaderBindings.h"


void UTankTurret::Rotate(float RelativeSpeed)
{
	//RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, +1.f);
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Rotation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator(0, Rotation, 0));
}