// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "RoadActor.h"
#include <Kismet/KismetMathLibrary.h>
#include <Runtime/Engine/Classes/Components/SplineComponent.h>
#include <Runtime/Engine/Classes/Components/SplineMeshComponent.h>



// Sets default values
ARoadActor::ARoadActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Build hirarchy
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	RootComponent = Spline;

	// Set default values
	DrawTrackPointNumbers = false;
}

// Called when the game starts or when spawned
void ARoadActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ARoadActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARoadActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	UStaticMesh* RoadMesh = static_cast<UStaticMesh*>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Game/Props/RoadMesh.RoadMesh"))); // TODO: Load from library class
	UStaticMesh* LeftRailMesh = static_cast<UStaticMesh*>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Game/Props/L_GuardRail.L_GuardRail")));
	UStaticMesh* RightRailMesh = static_cast<UStaticMesh*>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Game/Props/R_GuardRail.R_GuardRail")));

	uint32 SplinePoints = static_cast<uint32>(Spline->GetNumberOfSplinePoints());
	if(!Spline->IsClosedLoop())
		SplinePoints--;

	RoadDataArray.SetNum(Spline->GetNumberOfSplinePoints());

	for(uint32 Index = 0u; Index < SplinePoints; Index++)
	{
		BuildTrackElement(Index, RoadMesh);

		if(RoadDataArray[Index].LeftRail)
			BuildTrackElement(Index, LeftRailMesh);
		if(RoadDataArray[Index].RightRail)
			BuildTrackElement(Index, RightRailMesh);
	}

	if(DrawTrackPointNumbers)
	{
		for(uint32 Index = 0u; Index < SplinePoints; Index++)
		{
			UTextRenderComponent* TextRenderComp = NewObject<UTextRenderComponent>(this);
			TextRenderComp->RegisterComponent();

			TextRenderComp->SetupAttachment(Spline);
			TextRenderComp->CreationMethod = EComponentCreationMethod::UserConstructionScript;

			FVector Location;
			FVector Tangent;
			Spline->GetLocalLocationAndTangentAtSplinePoint(Index, Location, Tangent);
			FTransform RelTransform = FTransform(UKismetMathLibrary::MakeRotFromX(Tangent * -1), Location + FVector(0.f, 0.f, 50.f), FVector(1.f, 1.f, 1.f));
			TextRenderComp->SetRelativeTransform(RelTransform);

			TextRenderComp->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
			TextRenderComp->WorldSize = 300.f;

			TextRenderComp->SetText(FString::FromInt(Index));
		}
	}
}

void ARoadActor::BuildTrackElement(uint32 LoopIndex, UStaticMesh* TrackElementMesh)
{
	if(TrackElementMesh == nullptr)
		return;

	uint32 CurrentLoopIndex = LoopIndex;
	uint32 NextLoopIndex = (LoopIndex + 1) % Spline->GetNumberOfSplinePoints();

	// Get start and end values between points
	FVector StartLocation = Spline->GetLocationAtSplinePoint(CurrentLoopIndex, ESplineCoordinateSpace::World);
	FVector StartTangent = Spline->GetTangentAtSplinePoint(CurrentLoopIndex, ESplineCoordinateSpace::World);
	FVector EndLocation = Spline->GetLocationAtSplinePoint(NextLoopIndex, ESplineCoordinateSpace::World);
	FVector EndTangent = Spline->GetTangentAtSplinePoint(NextLoopIndex, ESplineCoordinateSpace::World);

	float StartRoll = RoadDataArray[LoopIndex].TrackBank;
	FVector2D StartScale = FVector2D(RoadDataArray[LoopIndex].TrackWidth, RoadDataArray[LoopIndex].TrackThickness);
	float EndRoll = RoadDataArray[NextLoopIndex].TrackBank;
	FVector2D EndScale = FVector2D(RoadDataArray[NextLoopIndex].TrackWidth, RoadDataArray[NextLoopIndex].TrackThickness);

	// Create spline mesh component
	USplineMeshComponent* SplineMeshComp = NewObject<USplineMeshComponent>(this);
	SplineMeshComp->RegisterComponent();

	SplineMeshComp->SetupAttachment(Spline);
	SplineMeshComp->CreationMethod = EComponentCreationMethod::UserConstructionScript;
	SplineMeshComp->bSmoothInterpRollScale = true;
	SplineMeshComp->SetMobility(EComponentMobility::Static);

	SplineMeshComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	SplineMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	// Load and set mesh
	SplineMeshComp->SetStaticMesh(TrackElementMesh);

	// Set start and end
	SplineMeshComp->SetStartAndEnd(StartLocation, StartTangent, EndLocation, EndTangent);
	SplineMeshComp->SetStartRoll(StartRoll);
	SplineMeshComp->SetEndRoll(EndRoll);
	SplineMeshComp->SetStartScale(StartScale);
	SplineMeshComp->SetEndScale(EndScale);
}

