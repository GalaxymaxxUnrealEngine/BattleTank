// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
//	UE_LOG(LogTemp, Warning, TEXT("ATankPlayerController ticking"));
}


void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	//UE_LOG(LogTemp, Warning, TEXT("AIController BeginPlay function"));

	// Test what tank is the player controller possessing
	ATank* ControlledTank = GetControlledTank();
	if (!ControlledTank) {
//		UE_LOG(LogTemp, Warning, TEXT("AIController not possessing a tank"));
	}
	else {
		FString TankName = ControlledTank->GetName();
//		UE_LOG(LogTemp, Warning, TEXT("The name of this tank is %s"), *TankName);
	}
}

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if(!GetControlledTank())
	{
		return;
	}

	FVector HitLocation;
	if(GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}
	// Get World location if linetrace through crosshair
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find the crosshair position in pixel coordinate
	int32 ViewportXAsix, ViewportYAsix;
	GetViewportSize(ViewportXAsix, ViewportYAsix);	// get the screen size
	auto ScreenLocation = FVector2D(ViewportXAsix*CrossHairXLocation, ViewportYAsix*CrossHairYLocation);	// use screen size and ratio to get the crosshair position
	FVector LookDirection;
	if(GetLookDirection(ScreenLocation, LookDirection))
	{
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	// Line-trace along that LookDirection, and see what we hit (up to max range)
	
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const	// change the position of the crosshair in 2D to a 3D direction
{
	// Deproject the 2D viewport location to a 3d direction
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection*LineTrackRange);
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility
	))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	else // if the crosshair didn't hit anything ( For example: sky )
	{
		HitLocation = FVector(0);
		return false;
	}
	
}
