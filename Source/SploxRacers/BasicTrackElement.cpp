// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "BasicTrackElement.h"
#include <Runtime/Engine/Classes/Components/SplineMeshComponent.h>

ABasicTrackElement::ABasicTrackElement() : SplineMeshComponent(nullptr)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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
	SplineMeshComponent = CreateDefaultSubobject<USplineMeshComponent>(TEXT("MeshComponent"));
	SplineMeshComponent->SetStaticMesh(Mesh);
	SplineMeshComponent->bSmoothInterpRollScale = true;
	SplineMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	SplineMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	RootComponent = SplineMeshComponent;
}
