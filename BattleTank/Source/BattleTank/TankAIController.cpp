// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

    auto ControlledTankName = GetControlledTank();
    auto PlayerTankName = GetPlayerTank();

    if (!ControlledTankName)
    {
        UE_LOG(LogTemp, Warning, TEXT("AI Controlled Tank not found."));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController is possessing tank:  %s"), *(ControlledTankName->GetName()));
    }  

    if (!PlayerTankName)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player Controlled Tank not found."));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController is seeing player tank:  %s"), *(PlayerTankName->GetName()));
    }  
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    auto HitLocation = GetPlayerTank()->GetActorLocation();
    GetControlledTank()->AimAt(HitLocation);
}

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

    if (!PlayerTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player Tank not found by AI"));
        return nullptr;
    }
    else { return Cast<ATank>(PlayerTank); }
}