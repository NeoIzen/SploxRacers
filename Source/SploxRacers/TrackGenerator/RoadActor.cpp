// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "RoadActor.h"
#include "TrackElementID.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"

ARoadActor::ARoadActor()
{
	// The track will never tic
	PrimaryActorTick.bCanEverTick = false;

	// Build hierarchy
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	Spline->SetMobility(EComponentMobility::Static);
	RootComponent = Spline;

	// Set default values
	DrawTrackPointNumbers = false;
}

USplineComponent* ARoadActor::GetSpline() const
{
	return Spline;
}

void ARoadActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	UnregisterAllComponents();

	if(!TrackPartLibraryClass)
		return;

	TrackPartLibrary = NewObject<UTrackPartLibrary>(this, TrackPartLibraryClass);

	TrackElements.Empty();

	uint32 NumSplinePoints = static_cast<uint32>(Spline->GetNumberOfSplinePoints());
	// If it's not a closed track, remove one element
	if(!Spline->IsClosedLoop())
		NumSplinePoints--;

	// TODO: Make sure the spline always has at least 2 points
	RoadDataArray.SetNum(Spline->GetNumberOfSplinePoints());
	SetStartValues();

	// Create track elements between all spline points
	for(uint32 Index = 0u; Index < NumSplinePoints; Index++)
	{
		if(RoadDataArray[Index].RoadElementID == ETrackElementID::Invalid ||
			RoadDataArray[Index].RoadElementID == ETrackElementID::LeftGuardRail ||
			RoadDataArray[Index].RoadElementID == ETrackElementID::RightGuardRail)
		{
			RoadDataArray[Index].RoadElementID = ETrackElementID::Road;
		}

		BuildTrackElement(Index, TrackPartLibrary->GetTrackPart(RoadDataArray[Index].RoadElementID));

		// Create rail guards if they are enabled
		if(RoadDataArray[Index].LeftRail)
			BuildTrackElement(Index, TrackPartLibrary->GetTrackPart(ETrackElementID::LeftGuardRail));
		if(RoadDataArray[Index].RightRail)
			BuildTrackElement(Index, TrackPartLibrary->GetTrackPart(ETrackElementID::RightGuardRail));
	}

	// Helper to build a track
	// Draw the spline point numbers on top of them to find the right array element corresponding to the spline point
	if(DrawTrackPointNumbers)
	{
		for(uint32 Index = 0u; Index < NumSplinePoints; Index++)
		{
			UTextRenderComponent* TextRenderComp = NewObject<UTextRenderComponent>(this);

			TextRenderComp->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
			TextRenderComp->CreationMethod = EComponentCreationMethod::UserConstructionScript;

			FVector Location;
			FVector Tangent;
			Spline->GetLocationAndTangentAtSplinePoint(Index, Location, Tangent, ESplineCoordinateSpace::Local);
			FTransform RelTransform = FTransform(UKismetMathLibrary::MakeRotFromX(Tangent * -1), Location + FVector(0.f, 0.f, 50.f), FVector(1.f, 1.f, 1.f));
			TextRenderComp->SetRelativeTransform(RelTransform);

			TextRenderComp->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
			TextRenderComp->WorldSize = 300.f;

			TextRenderComp->SetText(FText::AsNumber(Index));

			TextRenderComp->RegisterComponent();
		}
	}
}

void ARoadActor::SetStartValues()
{
	// Make the start element to be always a certain way
	RoadDataArray[0].TrackBank = 0.f;
	RoadDataArray[0].TrackWidth = 1.f;
	RoadDataArray[0].TrackThickness = 1.f;
	RoadDataArray[0].RoadElementID = ETrackElementID::Start;

	RoadDataArray[1].TrackBank = 0.f;
	RoadDataArray[1].TrackWidth = 1.f;
	RoadDataArray[1].TrackThickness = 1.f;

	// Make sure the second point has always a certain distance to the first
	FVector Location0 = Spline->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::Local);
	FVector Location1 = Spline->GetLocationAtSplinePoint(1, ESplineCoordinateSpace::Local);

	const float DesiredDistance = 1000.f; // 10m
	if(FVector::Dist(Location0, Location1) < DesiredDistance)
	{
		FVector Direction = Location1 - Location0;
		Direction.Normalize();

		Spline->SetLocationAtSplinePoint(1, Location0 + Direction * DesiredDistance, ESplineCoordinateSpace::Local);
	}
}

void ARoadActor::BuildTrackElement(uint32 LoopIndex, TSubclassOf<ABasicTrackElement> ElementClass)
{
	if(!ElementClass)
		return;

	uint32 CurrentLoopIndex = LoopIndex;
	uint32 NextLoopIndex = (LoopIndex + 1) % Spline->GetNumberOfSplinePoints(); // Wrap around so after the last we get the first point

	// Get start and end values between points
	FVector StartLocation = Spline->GetLocationAtSplinePoint(CurrentLoopIndex, ESplineCoordinateSpace::World);
	FVector StartTangent = Spline->GetTangentAtSplinePoint(CurrentLoopIndex, ESplineCoordinateSpace::World);
	FVector EndLocation = Spline->GetLocationAtSplinePoint(NextLoopIndex, ESplineCoordinateSpace::World);
	FVector EndTangent = Spline->GetTangentAtSplinePoint(NextLoopIndex, ESplineCoordinateSpace::World);

	float StartRoll = RoadDataArray[LoopIndex].TrackBank;
	FVector2D StartScale = FVector2D(RoadDataArray[LoopIndex].TrackWidth, RoadDataArray[LoopIndex].TrackThickness);
	float EndRoll = RoadDataArray[NextLoopIndex].TrackBank;
	FVector2D EndScale = FVector2D(RoadDataArray[NextLoopIndex].TrackWidth, RoadDataArray[NextLoopIndex].TrackThickness);

	// Create track element
	UChildActorComponent* ChildActorComponent = NewObject<UChildActorComponent>(this);
	ChildActorComponent->SetMobility(EComponentMobility::Static);
	ChildActorComponent->SetChildActorClass(ElementClass);
	ChildActorComponent->CreationMethod = EComponentCreationMethod::UserConstructionScript; // Make sure a rebuild deletes all
	ChildActorComponent->CreateChildActor();
	ChildActorComponent->RegisterComponent();
	ChildActorComponent->AttachToComponent(Spline, FAttachmentTransformRules::KeepWorldTransform);

	TrackElements.Add(ChildActorComponent);

	// Set values
	ABasicTrackElement* const TrackElement = static_cast<ABasicTrackElement*>(ChildActorComponent->GetChildActor());
	TrackElement->Initialize();
	TrackElement->AttachToComponent(Spline, FAttachmentTransformRules::KeepWorldTransform);
	TrackElement->SetStartAndEnd(StartLocation, StartTangent, EndLocation, EndTangent);
	TrackElement->SetRoll(StartRoll, EndRoll);
	TrackElement->SetScale(StartScale, EndScale);
}
