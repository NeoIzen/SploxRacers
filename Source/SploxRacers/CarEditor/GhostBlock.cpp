// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "GhostBlock.h"
#include "BlockLibrary.h"

AGhostBlock::AGhostBlock()
{
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);

	// Set default values
	Enabled = false;
	GhostID = -1;

	// Set properties
	Properties.BlockName = "Ghost Block";
	Properties.Weight = 0.f;
}

// Called when the game starts or when spawned
void AGhostBlock::BeginPlay()
{
	Super::BeginPlay();

	//Material->SetScalarParameterValue(TEXT("Opacity"), 0.75f);
}

void AGhostBlock::Disable()
{
	Enabled = false;
	SetActorHiddenInGame(!Enabled);
}

void AGhostBlock::Enable()
{
	if(GhostID == -1)
		SetGhostID(1); // Adjust if default block changes

	Enabled = true;
	SetActorHiddenInGame(!Enabled);
}

bool AGhostBlock::IsActive() const
{
	return Enabled;
}

void AGhostBlock::SetGhostID_Implementation(int32 ID)
{
	// Set ID
	GhostID = ID;
}

int32 AGhostBlock::GetGhostID() const
{
	return GhostID;
}
