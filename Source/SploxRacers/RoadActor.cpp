// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "RoadActor.h"
#include "TrackElements.h"
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
	Spline->SetMobility(EComponentMobility::Static);
	RootComponent = Spline;

	// Set default values
	DrawTrackPointNumbers = false;
}

// Called when the game starts or when spawned
void ARoadActor::BeginPlay()
{
	Super::BeginPlay();

}

void ARoadActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	uint32 SplinePoints = static_cast<uint32>(Spline->GetNumberOfSplinePoints());
	if(!Spline->IsClosedLoop())
		SplinePoints--;

	RoadDataArray.SetNum(Spline->GetNumberOfSplinePoints());

	for(uint32 Index = 0u; Index < SplinePoints; Index++)
	{
		if(Index == 0u)
			BuildTrackElement(Index, AStartElement::StaticClass());
		else
		{
			switch(RoadDataArray[Index].RoadElementID)
			{
			case 2: // Speed
				break;
			case 1: // Normal
			default:
				BuildTrackElement(Index, ATrackElement::StaticClass());
			}
		}

		if(RoadDataArray[Index].LeftRail)
			BuildTrackElement(Index, ALeftGuardRailElement::StaticClass());
		if(RoadDataArray[Index].RightRail)
			BuildTrackElement(Index, ARightGuardRailElement::StaticClass());
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

			TextRenderComp->SetText(FText::AsNumber(Index));//  FString::FromInt(Index));
		}
	}
}

void ARoadActor::BuildTrackElement(uint32 LoopIndex, TSubclassOf<AActor> InClass)
{
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

	// Create track element
	UChildActorComponent* TrackElement = NewObject<UChildActorComponent>(this);
	TrackElement->SetMobility(EComponentMobility::Static);
	TrackElement->RegisterComponent();
	TrackElement->SetChildActorClass(InClass);
	TrackElement->CreationMethod = EComponentCreationMethod::UserConstructionScript;
	TrackElement->CreateChildActor();
	TrackElement->SetupAttachment(Spline);
	TrackElement->GetChildActor()->AttachToComponent(Spline, FAttachmentTransformRules::KeepWorldTransform);

	// Set values
	ABasicTrackElement* const BasicTrackElement = static_cast<ABasicTrackElement*>(TrackElement->GetChildActor());
	BasicTrackElement->SetStartAndEnd(StartLocation, StartTangent, EndLocation, EndTangent);
	BasicTrackElement->SetRoll(StartRoll, EndRoll);
	BasicTrackElement->SetScale(StartScale, EndScale);
}
