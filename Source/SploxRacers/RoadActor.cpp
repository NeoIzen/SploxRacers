// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "RoadActor.h"
#include <Runtime/Engine/Classes/Components/SplineComponent.h>
#include <Runtime/Engine/Classes/Components/SplineMeshComponent.h>


// Sets default values
ARoadActor::ARoadActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Build hirarchy
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	Spline->AttachToComponent(SceneRoot, FAttachmentTransformRules::KeepRelativeTransform);

	// Set default values
	Spacing = 1.0f;
}

// Called when the game starts or when spawned
void ARoadActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoadActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ARoadActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	uint32 lidx = Spline->GetSplineLength() / Spacing;

	for(uint32 i = 0u; i <= lidx; i++)
	{
		float Distance = i * Spacing;

		// Create spline mesh component
		auto splineMesh = NewObject<USplineMeshComponent>(this);
		splineMesh->SetupAttachment(Spline);
		splineMesh->CreationMethod = EComponentCreationMethod::UserConstructionScript;
		splineMesh->RegisterComponent();

		// Activate collision
		splineMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

		// Load and set mesh
		auto staticMesh = static_cast<UStaticMesh*>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Game/Meshes/RoadMesh.RoadMesh")));
		splineMesh->SetStaticMesh(staticMesh); // TODO: Load from library class

		// Load and set material
		auto material = static_cast<UMaterial*>(StaticLoadObject(UMaterial::StaticClass(), nullptr, TEXT("/Game/Materials/RoadMaterial.RoadMaterial")));
		splineMesh->SetMaterial(0, material);

		// Set start and end
		splineMesh->SetStartAndEnd(Spline->GetWorldLocationAtDistanceAlongSpline(Distance),
			Spline->GetWorldTangentAtDistanceAlongSpline(Distance),
			Spline->GetWorldLocationAtDistanceAlongSpline(Distance + Spacing),
			Spline->GetWorldTangentAtDistanceAlongSpline(Distance + Spacing));
	}
}

