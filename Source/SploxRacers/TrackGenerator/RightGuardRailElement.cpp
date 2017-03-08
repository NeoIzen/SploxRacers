// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "RightGuardRailElement.h"

UStaticMesh* ARightGuardRailElement::Mesh = nullptr;

ARightGuardRailElement::ARightGuardRailElement() : ABasicTrackElement()
{
	/* Load resources */
	if(Mesh == nullptr)
		Mesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/Props/R_GuardRail.R_GuardRail")).Object;

	/* Create and configure spline mesh */
	CreateSplineMeshComponent(Mesh);
}
