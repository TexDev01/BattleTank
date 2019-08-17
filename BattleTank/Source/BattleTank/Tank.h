// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/DefaultPawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class AProjectile;
class UTankAimingComponent;
class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

	void AimAt(FVector HitLocation);

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=ComponentVariables)
	UTankMovementComponent* TankMovementComponent = nullptr;

private:
	ATank();

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UTankBarrel* Barrel = nullptr;
	float ReloadTimeInSeconds = 3;
	double LastFireTime = 0;

	UPROPERTY(EditDefaultsOnly, Category=Firing)
	float LaunchSpeed = 4000;  //Sensible starting value 1000 m/s

	UPROPERTY(EditDefaultsOnly, Category=Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;
};
