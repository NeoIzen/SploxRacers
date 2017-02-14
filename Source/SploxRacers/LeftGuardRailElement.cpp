// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "LeftGuardRailElement.h"

UStaticMesh* ALeftGuardRailElement::Mesh = nullptr;

ALeftGuardRailElement::ALeftGuardRailElement() : ABasicTrackElement()
{
	if(Mesh == nullptr)
		Mesh = static_cast<UStaticMesh*>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Game/Props/L_GuardRail.L_GuardRail")));

	CreateSplineMeshComponent(Mesh);
}
