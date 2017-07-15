// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
    // TODO Clamp actual throttle valu so player can't over-drive
    auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    // AddForceAtLocation would not apply an accelaration
    TankRoot->AddImpulseAtLocation(ForceApplied, ForceLocation); // TODO add max speed
}


