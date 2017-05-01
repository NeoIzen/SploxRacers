// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "BasicTrackElement.h"

ABasicTrackElement::ABasicTrackElement()
{
}

void ABasicTrackElement::Initialize()
{
	// Create mesh component and set static mesh
	SplineMeshComponent = NewObject<USplineMeshComponent>(this);
	SplineMeshComponent->SetStaticMesh(StaticMesh);
	SplineMeshComponent->bSmoothInterpRollScale = true;

	// Enable collision
	SplineMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	SplineMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	SplineMeshComponent->RegisterComponent();

	RootComponent = SplineMeshComponent;
}

void ABasicTrackElement::SetStartAndEnd(FVector StartPos, FVector StartTangent, FVector EndPos, FVector EndTangent)
{
	SplineMeshComponent->SetStartAndEnd(StartPos, StartTangent, EndPos, EndTangent);
}

void ABasicTrackElement::SetRoll(float StartRoll, float EndRoll)
{
	SplineMeshComponent->SetStartRoll(StartRoll);
	SplineMeshComponent->SetEndRoll(EndRoll);
}

void ABasicTrackElement::SetScale(FVector2D StartScale, FVector2D EndScale)
{
	SplineMeshComponent->SetStartScale(StartScale);
	SplineMeshComponent->SetEndScale(EndScale);
}
