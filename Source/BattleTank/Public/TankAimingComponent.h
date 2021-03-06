// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"



// Forward Declaration
class UTankBarrel;	
class UTankTurret;

// Holds barrel's properities and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelReference(UTankBarrel* Barrel);
	void SetTurretReference(UTankTurret* Turret);

	// TODO setTurretReference

	void AimAt(FVector HitLocation,float LaunchSpeed);

	
	
private:
	UTankBarrel* Barrel = nullptr;	// let TankAimingComponent can use the function declared in TankBarrel
	UTankTurret* Turret = nullptr;

	void MoveBarrelTowards(FVector AimDirection);
		
	
};
