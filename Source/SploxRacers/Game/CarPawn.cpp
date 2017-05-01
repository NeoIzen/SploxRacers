// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "CarPawn.h"
#include "SploxRacersGameState.h"
#include "WheelBlock.h"
#include "TrackGenerator/RoadActor.h"
#include "Components/SplineComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

ACarPawn::ACarPawn()
{
	// Create a spring arm component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->TargetOffset = FVector(0.f, 0.f, 200.f);
	SpringArm->SetRelativeRotation(FRotator(-15.f, 90.f, 0.f));
	SpringArm->TargetArmLength = 600.0f;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraRotationLagSpeed = 7.f;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	RootComponent = SpringArm;

	// Create camera component 
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = false;
	Camera->FieldOfView = 90.f;
	Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform);
}

void ACarPawn::Initialize(ARoadActor* Road)
{
	if(!Road)
		return;

	USplineComponent* RoadSpline = Road->GetSpline();

	// Set transform
	FVector Location = FVector();
	FVector Tangent = FVector();
	FVector Scale = FVector(2.f, 2.f, 2.f);

	RoadSpline->GetLocationAndTangentAtSplinePoint(0, Location, Tangent, ESplineCoordinateSpace::World);

	// Enable physics
	UStaticMeshComponent* Mesh = Cast<UStaticMeshComponent>(GetRootComponent());
	Mesh->SetSimulatePhysics(true);
	Mesh->SetEnableGravity(true);

	Mesh->SetWorldTransform(FTransform(UKismetMathLibrary::MakeRotFromX(Tangent * -1), Location + FVector(0.f, 0.f, 200.f), Scale));

	// Setup vehicle movement
	SetupWheels();
}

void ACarPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Throttle", this, &ACarPawn::Throttle);
	PlayerInputComponent->BindAxis("Steer", this, &ACarPawn::Steer);

	PlayerInputComponent->BindAction("Handbrake", IE_Pressed, this, &ACarPawn::Handbrake<true>);
	PlayerInputComponent->BindAction("Handbrake", IE_Released, this, &ACarPawn::Handbrake<false>);
}

void ACarPawn::Tick(float Delta)
{
	Super::Tick(Delta);

}

void ACarPawn::SetupWheels()
{
	TArray<UActorComponent*> WheelComponents = GetComponentsByClass(UWheelBlock::StaticClass());

	for(UActorComponent* Component : WheelComponents)
	{
		UWheelBlock* Wheel = Cast<UWheelBlock>(Component);

		Wheel->InitializeWheel();

		Wheels.Add(Wheel);
	}
}

void ACarPawn::Throttle(float Val)
{
	float Force = Val * 500000.f;
	for(UWheelBlock* Wheel : Wheels)
	{
		FVector Torque = Wheel->GetPhysicsConstraintWheel()->GetRightVector() * Force;

		Wheel->AddTorque(Torque);
	}
}

void ACarPawn::Steer(float Val)
{
}

void ACarPawn::Handbrake(bool Pressed)
{
}
