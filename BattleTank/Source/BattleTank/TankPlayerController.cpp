// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();

    auto ControlledTankName = GetControlledTank();

    if (!ControlledTankName)
    {
        UE_LOG(LogTemp, Warning, TEXT("ControlledTankName pointer not created."));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController is possessing tank:  %s"), *(ControlledTankName->GetName()));
    }  
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    AimTowardsCrosshair();
    return;
}

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if (!GetControlledTank()) { return; }

    FVector HitLocation;
    if (GetSightRayHitLocation(HitLocation))
    {
        GetControlledTank()->AimAt(HitLocation);
        //UE_LOG(LogTemp, Warning, TEXT("Look direction:  %s"), *HitLocation.ToString());
    }
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);

    auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
    
    FVector LookDirection;
    if (GetLookDirection(ScreenLocation, LookDirection))
    {
        GetLookVectorHitLocation(LookDirection, HitLocation);
    }

    return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    FVector CameraWorldLocation;
    return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
    FHitResult HitResult;
    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

    if(GetWorld()->LineTraceSingleByChannel(
        HitResult,
        StartLocation,
        EndLocation,
        ECollisionChannel::ECC_Visibility))
    {
        HitLocation = HitResult.Location; 
        return true;
    }
    HitLocation = FVector(0);
    return false;
}