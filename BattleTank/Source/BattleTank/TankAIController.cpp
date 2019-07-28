// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

    auto ControlledTankName = GetControlledTank();

    if (!ControlledTankName)
    {
        UE_LOG(LogTemp, Warning, TEXT("AI Controlled Tank not found."));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController is possessing tank:  %s"), *(ControlledTankName->GetName()));
    }  
}

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}