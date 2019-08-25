// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Math/UnrealMathUtility.h"

UTankTrack::UTankTrack()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
    OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    DriveTrack();
    ApplySidewaysForce();
    CurrentThrottle = 0;
}

void UTankTrack::ApplySidewaysForce()
{
    // Workout the required acceleration this frame to correct
    auto SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
    auto DeltaTime = GetWorld()->GetDeltaSeconds();
    auto CounterAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
    
    // Calculate and apply sidways force f=ma
    auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    auto SidewaysForce = (CounterAcceleration * TankRoot->GetMass()) / 2;
    TankRoot->AddForce(SidewaysForce);
}

void UTankTrack::SetThrottle(float Throttle)
{ 
    CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTrack()
{
    auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}