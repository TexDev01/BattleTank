// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
    UE_LOG(LogTemp, Warning, TEXT("%f:  Barrel elevate:  %f"), (GetWorld()->GetRealTimeSeconds()), RelativeSpeed);
}