// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "StartElement.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SplineMeshComponent.h"
#include <algorithm>

AStartElement::AStartElement() : ABasicTrackElement()
{
}

void AStartElement::Initialize()
{
	Super::Initialize();

	/* Create goal line trigger */
	TriggerArea = NewObject<UBoxComponent>(this);
	TriggerArea->RegisterComponent();
	TriggerArea->AttachToComponent(SplineMeshComponent, FAttachmentTransformRules::KeepRelativeTransform);

	// Make the trigger area to fit the mesh width
	FVector Extend = FVector(75.f, SplineMeshComponent->GetStaticMesh()->GetBoundingBox().GetExtent().Y, 500.f);
	TriggerArea->SetBoxExtent(Extend);

	/* Create goal line decal */
	Decal = NewObject<UDecalComponent>(this);
	Decal->RegisterComponent();
	Decal->AttachToComponent(TriggerArea, FAttachmentTransformRules::KeepRelativeTransform); // Attach to trigger area, so the position updates automatically when the trigger moves

	std::swap(Extend.X, Extend.Z);
	Extend.Y -= 100.f; // Shrink the decal, so it doesn't paint onto the rails
	Decal->DecalSize = Extend;

	// Rotate decal so it points down onto the track and replace it, since the local axis won't match up with the world anymore
	Decal->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -Extend.X), FRotator::MakeFromEuler(FVector(0.f, 90.f, 0.f)));

	/* Create decal material*/
	// Create and set the goal line material to the decal
	UMaterialInstanceDynamic* DynDecalMaterial = UMaterialInstanceDynamic::Create(DecalMaterial, this);
	// Calculate the Y to Z ratio to make the texture checkers always squared
	DynDecalMaterial->SetScalarParameterValue(FName(TEXT("YZRatio")), Extend.Y / Extend.Z);
	// Increase the amount of checker squares
	DynDecalMaterial->SetScalarParameterValue(FName(TEXT("Tiling")), 2.f);
	Decal->SetDecalMaterial(DynDecalMaterial);
}

void AStartElement::SetStartAndEnd(FVector StartPos, FVector StartTangent, FVector EndPos, FVector EndTangent)
{
	Super::SetStartAndEnd(StartPos, StartTangent, EndPos, EndTangent);

	// Get rotation from the endpoint of the element
	FRotator Rotation = UKismetMathLibrary::MakeRotFromX(EndTangent * -1.f);

	// Place trigger to the end of the element
	TriggerArea->SetWorldLocationAndRotation(EndPos, Rotation);
	// Offset so it is on top of it and the end side touched the endpoint
	TriggerArea->AddLocalOffset(FVector(TriggerArea->GetUnscaledBoxExtent().X, 0.f, TriggerArea->GetUnscaledBoxExtent().Z));
}

void AStartElement::SetRoll(float StartRoll, float EndRoll)
{
	Super::SetRoll(StartRoll, EndRoll);
}

void AStartElement::SetScale(FVector2D StartScale, FVector2D EndScale)
{
	Super::SetScale(StartScale, EndScale);
}
