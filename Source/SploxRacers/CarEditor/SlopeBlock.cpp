// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "SlopeBlock.h"

ASlopeBlock::ASlopeBlock()
{
	StaticMeshComponent->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/Meshes/SlopeBlock.SlopeBlock")).Object);

	// Set properties
	Properties.BlockName = "Chassis Slope Block";
	Properties.Weight = 10.f;
}

int32 ASlopeBlock::GetID() const
{
	return 2;
}