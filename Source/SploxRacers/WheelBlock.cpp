// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "WheelBlock.h"
#include "VehicleWheel.h"
#include "CarPawnBase.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

void UWheelBlock::InitializeWheel()
{
	PhysicsConstraintWheel = NewObject<UPhysicsConstraintComponent>(this);
	PhysicsConstraintWheel->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
	PhysicsConstraintWheel->SetRelativeLocation(FVector::ZeroVector);

	PhysicsConstraintWheel->SetDisableCollision(true);
	PhysicsConstraintWheel->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0.f);
	PhysicsConstraintWheel->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0.f);
	PhysicsConstraintWheel->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Free, 0.f);

	UBasicBlock* Body = Cast<UBasicBlock>(Cast<ACarPawnBase>(GetOuter()->GetOuter())->GetRootComponent());
	PhysicsConstraintWheel->SetConstrainedComponents(Body, NAME_None, this, NAME_None);

	SetPhysicsMaxAngularVelocity(1000.f);
}

UPhysicsConstraintComponent* UWheelBlock::GetPhysicsConstraintWheel()
{
	return PhysicsConstraintWheel;
}
