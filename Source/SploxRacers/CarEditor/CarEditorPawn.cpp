// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "CarEditorPawn.h"
#include "GhostBlock.h"

// Sets default values
ACarEditorPawn::ACarEditorPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create hirarchy
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	SpringArm->TargetArmLength = 1000.0f;
	SpringArm->SetRelativeRotation(FQuat(-FVector(0.f, 1.f, 0.f), FMath::DegreesToRadians(315.0f)));
	RootComponent = SpringArm;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform);

	// Set defaults
	RotationSpeed = 100.0f;
}

// Called when the game starts or when spawned
void ACarEditorPawn::BeginPlay()
{
	Super::BeginPlay();

	// Activate mouse cursor
	APlayerController* PC = Cast<APlayerController>(GetController());

	if(PC)
	{
		PC->bShowMouseCursor = true;
		PC->bEnableClickEvents = true;
		PC->bEnableMouseOverEvents = true;
	}

	// Create ghost block
	GhostBlock = GetWorld()->SpawnActor<AGhostBlock>();
}

// Called every frame
void ACarEditorPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Rotate camera
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += CameraInput * RotationSpeed * DeltaTime;
	SetActorRotation(NewRotation);

	// Detect block underneath cursor
	APlayerController* PC = Cast<APlayerController>(GetController());

	if(PC)
	{
		FHitResult HitResult;
		if(PC->GetHitResultUnderCursor(ECollisionChannel::ECC_WorldStatic, false, HitResult))
		{
			GhostBlock->SetActorHiddenInGame(false);
			GhostBlock->SetActorLocation(HitResult.ImpactPoint);
		}
		else
		{
			GhostBlock->SetActorHiddenInGame(true);
		}
	}
}

// Called to bind functionality to input
#pragma warning(suppress:4458)
void ACarEditorPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("RotateCameraHorizontal", this, &ACarEditorPawn::RotateCamera);
}

void ACarEditorPawn::RotateCamera(float AxisValue)
{
	CameraInput = AxisValue;
}

