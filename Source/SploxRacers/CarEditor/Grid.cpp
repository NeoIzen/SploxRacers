// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "Grid.h"

UGrid::UGrid()
{
	CellSize = FVector(1, 1, 1);
	CellCount = FVector(10, 10, 10);
}

FVector UGrid::GetGridLocationFromWorld(FVector WorldLocation)
{
	FVector CellLocation;

	CellLocation.X = FMath::FloorToInt(WorldLocation.X / (CellSize.X / 2.f));
	CellLocation.Y = FMath::FloorToInt(WorldLocation.Y / (CellSize.Y / 2.f));
	CellLocation.Z = FMath::FloorToInt(WorldLocation.Z / (CellSize.Z / 2.f));

	return CellLocation;
}

