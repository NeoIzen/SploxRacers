// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "StartElement.h"
#include <Runtime/Engine/Classes/Components/SplineMeshComponent.h>

UStaticMesh* AStartElement::Mesh = nullptr;

AStartElement::AStartElement() : ABasicTrackElement()
{
	if(Mesh == nullptr)
		Mesh = static_cast<UStaticMesh*>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Game/Props/RoadMesh.RoadMesh")));

	CreateSplineMeshComponent(Mesh);

	/*TriggerArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	TriggerArea->AttachToComponent(MeshComponent, FAttachmentTransformRules::KeepRelativeTransform);
	TriggerArea->SetBoxExtent(Mesh->GetBoundingBox().GetExtent());*/
}

