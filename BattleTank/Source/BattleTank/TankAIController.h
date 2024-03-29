// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "AIController.h"
#include "GameFramework/Controller.h"
#include "TankAIController.generated.h"

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 8000;

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnPossessedTankDeath();

	virtual void SetPawn(APawn* InPawn) override;
};
