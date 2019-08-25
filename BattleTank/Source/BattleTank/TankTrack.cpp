// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
    OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    UE_LOG(LogTemp, Warning, TEXT("I'm Hit"));
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    // Calculate the slippage speed
    auto SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());

    // Workout the required acceleration this frame to correct
    auto CounterAcceleration = -SlippageSpeed * GetRightVector();
    
    // Calculate and apply sidways force f=ma
    auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    auto SidewaysForce = CounterAcceleration * TankRoot->GetMass();
    TankRoot->AddForce(SidewaysForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
    auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}