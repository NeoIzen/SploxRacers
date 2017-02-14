// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "RightGuardRailElement.h"

UStaticMesh* ARightGuardRailElement::Mesh = nullptr;

ARightGuardRailElement::ARightGuardRailElement() : ABasicTrackElement()
{
	if(Mesh == nullptr)
		Mesh = static_cast<UStaticMesh*>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Game/Props/R_GuardRail.R_GuardRail")));

	CreateSplineMeshComponent(Mesh);
}
