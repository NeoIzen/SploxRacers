// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "VehiclePawn.h"
#include "Grid.h"
#include "SploxRacersGameState.h"
#include "SimpleWheeledVehicleMovementComponent.h"
#include "CoreUObject.h"

AVehiclePawn::AVehiclePawn(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer)
{
	// Create box component
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Box->SetCollisionObjectType(ECollisionChannel::ECC_Vehicle);
	Box->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	RootComponent = Box;

	// Create a spring arm component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->TargetOffset = FVector(0.f, 0.f, 200.f);
	SpringArm->SetRelativeRotation(FRotator(-15.f, 0.f, 0.f));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 600.0f;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraRotationLagSpeed = 7.f;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;

	// Create camera component 
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;
	Camera->FieldOfView = 90.f;

	// Set up vehicle movement component
	VehicleMovement = CreateDefaultSubobject<USimpleWheeledVehicleMovementComponent>(TEXT("VehicleMovement"));
	VehicleMovement->SetIsReplicated(true); // Enable replication by default
}

UGrid* AVehiclePawn::GetGrid()
{
	if(!Grid)
	{
		Grid = NewObject<UGrid>(GetWorld()->GetGameState());
	}

	return Grid;
}

void AVehiclePawn::Initialize(ABasicBlock* ParentBlock)
{
	VehicleMovement->SetUpdatedComponent(ParentBlock->GetRootComponent());

	ParentBlock->SetActorRotation(FRotator(0.f, -90.f, 0.f));
}

void AVehiclePawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Throttle", this, &AVehiclePawn::Throttle);
	PlayerInputComponent->BindAxis("Steer", this, &AVehiclePawn::Steer);
	PlayerInputComponent->BindAxis("LookUp");
	PlayerInputComponent->BindAxis("LookRight");

	PlayerInputComponent->BindAction("Handbrake", IE_Pressed, this, &AVehiclePawn::Handbrake<true>);
	PlayerInputComponent->BindAction("Handbrake", IE_Released, this, &AVehiclePawn::Handbrake<false>);
}

void AVehiclePawn::Tick(float Delta)
{
	Super::Tick(Delta);

}

UWheeledVehicleMovementComponent* AVehiclePawn::GetVehicleMovementComponent() const
{
	return VehicleMovement;
}

void AVehiclePawn::Throttle(float Val)
{
	GetVehicleMovementComponent()->SetThrottleInput(Val);
}

void AVehiclePawn::Steer(float Val)
{
	GetVehicleMovementComponent()->SetSteeringInput(Val);
}

void AVehiclePawn::Handbrake(bool Pressed)
{
	GetVehicleMovementComponent()->SetHandbrakeInput(Pressed);
}
