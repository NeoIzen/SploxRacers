// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "GhostBlock.h"

AGhostBlock::AGhostBlock()
{
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);

	StaticMeshComponent->SetMobility(EComponentMobility::Movable);
}
