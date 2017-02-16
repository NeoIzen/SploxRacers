// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "TrackElement.h"
#include <Runtime/Engine/Classes/Components/SplineMeshComponent.h>

UStaticMesh* ATrackElement::Mesh = nullptr;

ATrackElement::ATrackElement() : ABasicTrackElement()
{
	/* Load resources */
	if(Mesh == nullptr)
		Mesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/Props/RoadMesh.RoadMesh")).Object;

	/* Create and configure spline mesh */
	CreateSplineMeshComponent(Mesh);
}
