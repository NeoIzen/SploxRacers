// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "BasicTrackElement.h"
#include <Runtime/Engine/Classes/Components/SplineMeshComponent.h>

ABasicTrackElement::ABasicTrackElement() : SplineMeshComponent(nullptr)
{
	// The road doesn't need to tick
	PrimaryActorTick.bCanEverTick = false;
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

void ABasicTrackElement::CreateSplineMeshComponent(UStaticMesh* Mesh)
{
	// Create mesh component and set static mesh
	SplineMeshComponent = CreateDefaultSubobject<USplineMeshComponent>(TEXT("MeshComponent"));
	SplineMeshComponent->SetStaticMesh(Mesh);
	SplineMeshComponent->bSmoothInterpRollScale = true;
	// Enable collision
	SplineMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	SplineMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	// Set as root component
	RootComponent = SplineMeshComponent;
}