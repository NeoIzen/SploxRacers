// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "CarEditorPawn.h"
#include "GhostBlock.h"
#include "Grid.h"

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
	RotationSpeed = 100.f;
	ZoomSpeed = 1000.f;
	CameraInput = FVector2D::ZeroVector;
	CameraZoom = 0.f;
	BlockColor = FLinearColor(1.f, 1.f, 1.f);
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
		PC->bEnableMouseOverEvents = true;
	}

	// Create the start block
	StartBlock = GetWorld()->SpawnActor<ABasicBlock>(UGrid::GetInstance(this)->GetGridLocationFromWorldLocation(FVector(0.f, 0.f, 0.f)), FRotator(EForceInit::ForceInitToZero));

	// Create ghost block
	GhostBlock = GetWorld()->SpawnActor<AGhostBlock>();
}

// Called every frame
void ACarEditorPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Rotate camera
	FRotator NewRotation = GetActorRotation();
	NewRotation.Pitch = FMath::ClampAngle(NewRotation.Pitch + CameraInput.X * RotationSpeed * DeltaTime, -45.f, 45.f);
	NewRotation.Yaw += CameraInput.Y * RotationSpeed * DeltaTime;
	SetActorRotation(NewRotation);

	// Zoom camera
	SpringArm->TargetArmLength += CameraZoom * ZoomSpeed * DeltaTime;

	// Detect block underneath cursor
	APlayerController* PC = Cast<APlayerController>(GetController());

	if(PC)
	{
		FHitResult HitResult;
		if(PC->GetHitResultUnderCursor(ECollisionChannel::ECC_WorldStatic, false, HitResult) && Cast<ABasicBlock>(HitResult.Actor.Get()))
		{
			GhostBlock->Enable();

			// Calcuate ghost location
			FVector Location = UGrid::GetInstance(this)->GetGridLocationFromWorldLocation(HitResult.ImpactPoint + HitResult.Normal);
			GhostBlock->SetActorLocation(Location);
		}
		else
		{
			GhostBlock->Disable();
		}
	}
}

// Called to bind functionality to input
#pragma warning(suppress:4458)
void ACarEditorPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("RotateCameraHorizontal", this, &ACarEditorPawn::RotateCameraHorizontal);
	InputComponent->BindAxis("RotateCameraVertical", this, &ACarEditorPawn::RotateCameraVertical);
	InputComponent->BindAxis("ZoomCamera", this, &ACarEditorPawn::ZoomCamera);
	InputComponent->BindAction("PlaceBlock", IE_Pressed, this, &ACarEditorPawn::PlaceBlock);
}

void ACarEditorPawn::RotateCameraVertical(float AxisValue)
{
	CameraInput.X = AxisValue;
}

void ACarEditorPawn::RotateCameraHorizontal(float AxisValue)
{
	CameraInput.Y = AxisValue;
}

void ACarEditorPawn::ZoomCamera(float AxisValue)
{
	CameraZoom = AxisValue;
}

void ACarEditorPawn::PlaceBlock()
{
	if(!GhostBlock->IsActive())
		return;

	// Spawn new block
	FVector SpawnLocation = GhostBlock->GetActorLocation();
	ABasicBlock* NewBlock = GetWorld()->SpawnActor<ABasicBlock>(SpawnLocation, FRotator(EForceInit::ForceInitToZero));

	NewBlock->AttachToActor(StartBlock, FAttachmentTransformRules::KeepWorldTransform);

	NewBlock->SetColor(BlockColor.R, BlockColor.G, BlockColor.B);
}

void ACarEditorPawn::SetBlockColor(float r, float g, float b)
{
	BlockColor = FLinearColor(r, g, b);
	GhostBlock->SetColor(r, g, b);
}
