// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
    PrimaryComponentTick.bCanEverTick = false;
    OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::BeginPlay()
{
    Super::BeginPlay();
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    //UE_LOG(LogTemp, Warning, TEXT("DONKEY: Constructor called in c++"))
    // Drive the tracks
    DriveTrack();
    ApplySidewaysForce();
    // TODO implement max speed
    CurrentThrottle = 0;
}

void UTankTrack::ApplySidewaysForce()
{
    // Work-out the required acceleration this frame to correct
    auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());   
    auto DeltaTime = GetWorld()->GetDeltaSeconds();
    auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
    // Calculate and apply sideways force ( F= m a)
    auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // two tracks
    TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
    CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -MaxThrottle, MaxThrottle);
}

void UTankTrack::DriveTrack()
{
    auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot->AddImpulseAtLocation(ForceApplied, ForceLocation);
}




