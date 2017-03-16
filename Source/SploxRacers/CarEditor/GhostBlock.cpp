// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "GhostBlock.h"

AGhostBlock::AGhostBlock()
{
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);

	Enabled = false;

	ShouldRegisterToGrid = false;
}

// Called when the game starts or when spawned
void AGhostBlock::BeginPlay()
{
	Super::BeginPlay();

	Material->SetScalarParameterValue(TEXT("Opacity"), 0.75f);
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
