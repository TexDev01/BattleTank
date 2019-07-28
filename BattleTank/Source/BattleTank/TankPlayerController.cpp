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

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

