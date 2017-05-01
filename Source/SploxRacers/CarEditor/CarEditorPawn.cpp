// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "CarEditorPawn.h"
#include "GhostBlock.h"
#include "Grid.h"
#include "BlockLibrary.h"
#include "SeatBlock.h"

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

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->TargetArmLength = 100.0f;
	SpringArm->SetWorldRotation(FQuat(-FVector(0.f, 1.f, 0.f), FMath::DegreesToRadians(315.0f)));
	RootComponent = SpringArm;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform);

	// Set defaults
	StartBlockID = 1;

	RotationSpeed = 100.f;
	ZoomSpeed = 1000.f;
	CameraInput = FVector2D::ZeroVector;
	CameraZoom = 0.f;
}

// Called when the game starts or when spawned
void ACarEditorPawn::BeginPlay()
{
	Super::BeginPlay();

	// Create the start block
	GetGrid()->AddStartBlock(UBlockLibrary::GetInstance(this)->GetBlock(StartBlockID));
	GetGrid()->GetStartBlock()->CreateEditorGridCollision();

	// Create ghost block
	GhostBlock = GetWorld()->SpawnActor<AGhostBlock>();
	GhostBlock->SetBlockToGhost(UBlockLibrary::GetInstance(this)->GetBlock(StartBlockID + 1));
}

// Called every frame
void ACarEditorPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Rotate camera
	FRotator NewRotation = SpringArm->GetComponentRotation();
	NewRotation.Pitch = FMath::ClampAngle(NewRotation.Pitch + CameraInput.X * RotationSpeed * DeltaTime, -45.f, 45.f);
	NewRotation.Yaw += CameraInput.Y * RotationSpeed * DeltaTime;
	SpringArm->SetRelativeRotation(NewRotation);

	// Zoom camera
	SpringArm->TargetArmLength += CameraZoom * ZoomSpeed * DeltaTime;

	// Detect block underneath cursor
	FHitResult HitResult;
	if(Cast<APlayerController>(GetController())->GetHitResultUnderCursor(ECollisionChannel::ECC_WorldDynamic, false, HitResult))
	{
		UBoxComponent* GridCollider = Cast<UBoxComponent>(HitResult.Component.Get());
		if(GridCollider && GridCollider->GetOuter() && Cast<UBasicBlock>(GridCollider->GetOuter()))
		{
			FVector GridPoint = GetGrid()->GetGridPointFromWorldLocation(HitResult.Component->GetComponentLocation() + HitResult.Normal * Grid->CellSize);
			if(GetGrid()->IsValidGridPoint(GridPoint))
			{
				GhostBlock->Enable();

				// Calcuate ghost location
				FVector Location = GetGrid()->GetWorldLocationFromGridPoint(GridPoint);
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
	else
	{
		GhostBlock->Disable();
	}
}

// Called to bind functionality to input
void ACarEditorPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
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
	GetGrid()->AddBlock(GhostBlock->GetGhostedBlock()->GetClass(),
		GhostBlock->GetActorLocation(), GhostBlock->GetActorRotation(),
		GhostBlock->GetGhostedBlock()->GetColor())->CreateEditorGridCollision();
}

void ACarEditorPawn::RemoveBlock()
{
	// Detect block underneath cursor
	APlayerController* PC = Cast<APlayerController>(GetController());

	if(PC)
	{
		FHitResult HitResult;
		if(PC->GetHitResultUnderCursor(ECollisionChannel::ECC_WorldDynamic, false, HitResult))
		{
			UBoxComponent* GridCollider = Cast<UBoxComponent>(HitResult.Component.Get());
			if(GridCollider && GridCollider->GetOuter() && Cast<UBasicBlock>(GridCollider->GetOuter()))
			{
				UBasicBlock* Block = Cast<UBasicBlock>(GridCollider->GetOuter());

				GetGrid()->RemoveBlock(Block);
			}
		}
	}
}
