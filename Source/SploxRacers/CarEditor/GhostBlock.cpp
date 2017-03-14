// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "GhostBlock.h"

AGhostBlock::AGhostBlock()
{
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);

	//StaticMeshComponent->SetMaterial(0, ConstructorHelpers::FObjectFinder<UMaterialInterface>(TEXT("/Game/Materials/Car/GhostBlock.GhostBlock")).Object);

	Enabled = false;

	ShouldRegisterToGrid = false;
}

void AGhostBlock::Disable()
{
	Enabled = false;
	SetActorHiddenInGame(!Enabled);
}

void AGhostBlock::Enable()
{
	Enabled = true;
	SetActorHiddenInGame(!Enabled);
}

bool AGhostBlock::IsActive() const
{
	return Enabled;
}
