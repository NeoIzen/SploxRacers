// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "LeftGuardRailElement.h"

UStaticMesh* ALeftGuardRailElement::Mesh = nullptr;

ALeftGuardRailElement::ALeftGuardRailElement() : ABasicTrackElement()
{
	/* Load resources */
	if(Mesh == nullptr)
		Mesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/Props/L_GuardRail.L_GuardRail")).Object;

	/* Create and configure spline mesh */
	CreateSplineMeshComponent(Mesh);
}
