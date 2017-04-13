// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "CarEditorPawn.h"
#include "GhostBlock.h"
#include "Grid.h"
#include "BlockLibrary.h"
#include "CarEditorGameState.h"
#include <functional>

namespace
{
	enum class EDirection : int
	{
		Xp = 1,
		Xn,
		Yp,
		Yn,
		Zp,
		Zn,
		Vertical = Xp,
		Horizontal = Yp
	};
}

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
	if(StartBlockClass)
	{
		StartBlock = GetWorld()->SpawnActor<ABasicBlock>(StartBlockClass, UGrid::GetInstance(this)->GetGridLocationFromWorldLocation(FVector(0.f, 0.f, 0.f)), FRotator(EForceInit::ForceInitToZero));
		StartBlock->OnSpawn();
	}

	// Create ghost block
	if(GhostBlockClass)
		GhostBlock = GetWorld()->SpawnActor<AGhostBlock>(GhostBlockClass);
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
			UGrid* Grid = UGrid::GetInstance(this);
			if(Grid->IsValidGridPoint(Grid->GetGridPointFromWorldLocation(HitResult.ImpactPoint + HitResult.ImpactNormal)))
			{
				GhostBlock->Enable();

				// Calcuate ghost location
				FVector Location = Grid->GetGridLocationFromWorldLocation(HitResult.ImpactPoint + HitResult.Normal);
				GhostBlock->SetActorLocation(Location);
			}
			else
			{
				GhostBlock->Disable();
			}
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

	InputComponent->BindAxis("RotateCameraHorizontal", this, &ACarEditorPawn::RotateCamera<static_cast<int>(EDirection::Horizontal)>);
	InputComponent->BindAxis("RotateCameraVertical", this, &ACarEditorPawn::RotateCamera<static_cast<int>(EDirection::Vertical)>);
	InputComponent->BindAxis("ZoomCamera", this, &ACarEditorPawn::ZoomCamera);
	InputComponent->BindAction("RotateBlockX+", IE_Pressed, this, &ACarEditorPawn::RotateBlock<static_cast<int>(EDirection::Xp)>);
	InputComponent->BindAction("RotateBlockX-", IE_Pressed, this, &ACarEditorPawn::RotateBlock<static_cast<int>(EDirection::Xn)>);
	InputComponent->BindAction("RotateBlockY+", IE_Pressed, this, &ACarEditorPawn::RotateBlock<static_cast<int>(EDirection::Yp)>);
	InputComponent->BindAction("RotateBlockY-", IE_Pressed, this, &ACarEditorPawn::RotateBlock<static_cast<int>(EDirection::Yn)>);
	InputComponent->BindAction("RotateBlockZ+", IE_Pressed, this, &ACarEditorPawn::RotateBlock<static_cast<int>(EDirection::Zp)>);
	InputComponent->BindAction("RotateBlockZ-", IE_Pressed, this, &ACarEditorPawn::RotateBlock<static_cast<int>(EDirection::Zn)>);
	InputComponent->BindAction("PlaceBlock", IE_Pressed, this, &ACarEditorPawn::PlaceBlock);
	InputComponent->BindAction("RemoveBlock", IE_Pressed, this, &ACarEditorPawn::RemoveBlock);
}

AGhostBlock* ACarEditorPawn::GetGhostBlock()
{
	return GhostBlock;
}

void ACarEditorPawn::RotateCamera(int Direction, float AxisValue)
{
	switch(Direction)
	{
	case EDirection::Vertical:
		CameraInput.X = AxisValue;
		break;
	case EDirection::Horizontal:
		CameraInput.Y = AxisValue;
		break;
	}
}

void ACarEditorPawn::ZoomCamera(float AxisValue)
{
	CameraZoom = AxisValue;
}

void ACarEditorPawn::RotateBlock(int Direction)
{
	if(!GhostBlock->IsActive())
		return;

	FQuat Rotation = GhostBlock->GetActorRotation().Quaternion();
	switch(Direction)
	{
	case EDirection::Xp:
		Rotation = FQuat(FVector(1.f, 0.f, 0.f), FMath::DegreesToRadians(90.f)) * Rotation;
		break;
	case EDirection::Xn:
		Rotation = FQuat(FVector(-1.f, 0.f, 0.f), FMath::DegreesToRadians(90.f)) * Rotation;
		break;
	case EDirection::Yp:
		Rotation = FQuat(FVector(0.f, 1.f, 0.f), FMath::DegreesToRadians(90.f)) * Rotation;
		break;
	case EDirection::Yn:
		Rotation = FQuat(FVector(0.f, -1.f, 0.f), FMath::DegreesToRadians(90.f)) * Rotation;
		break;
	case EDirection::Zp:
		Rotation = FQuat(FVector(0.f, 0.f, 1.f), FMath::DegreesToRadians(90.f)) * Rotation;
		break;
	case EDirection::Zn:
		Rotation = FQuat(FVector(0.f, 0.f, -1.f), FMath::DegreesToRadians(90.f)) * Rotation;
		break;
	}
	GhostBlock->SetActorRotation(Rotation);
}

void ACarEditorPawn::PlaceBlock()
{
	if(!GhostBlock->IsActive())
		return;

	// Spawn new block
	FVector SpawnLocation = GhostBlock->GetActorLocation();
	FRotator SpawnRotation = GhostBlock->GetActorRotation();
	ABasicBlock* NewBlock = GetWorld()->SpawnActor<ABasicBlock>(UBlockLibrary::GetInstance(this)->GetBlock(GhostBlock->GetGhostID())->GetClass(),
		SpawnLocation, SpawnRotation);

	NewBlock->AttachToActor(StartBlock, FAttachmentTransformRules::KeepWorldTransform);

	NewBlock->SetColor(GhostBlock->GetColor());

	NewBlock->OnSpawn();
}

void ACarEditorPawn::RemoveBlock()
{
	// Detect block underneath cursor
	APlayerController* PC = Cast<APlayerController>(GetController());

	if(PC)
	{
		FHitResult HitResult;
		if(PC->GetHitResultUnderCursor(ECollisionChannel::ECC_WorldStatic, false, HitResult) && Cast<ABasicBlock>(HitResult.Actor.Get()))
		{
			ABasicBlock* Block = Cast<ABasicBlock>(HitResult.Actor.Get());

			UGrid::GetInstance(this)->RemoveBlockFromGrid(Block);
			Block->Destroy();
		}
	}
}
