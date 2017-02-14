// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "TrackElement.h"
#include <Runtime/Engine/Classes/Components/SplineMeshComponent.h>

UStaticMesh* ATrackElement::Mesh = nullptr;

ATrackElement::ATrackElement() : ABasicTrackElement()
{
	if(Mesh == nullptr)
		Mesh = static_cast<UStaticMesh*>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Game/Props/RoadMesh.RoadMesh")));

	CreateSplineMeshComponent(Mesh);
}
