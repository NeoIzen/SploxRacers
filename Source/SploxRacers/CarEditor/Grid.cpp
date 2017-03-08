// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "Grid.h"

UGrid::UGrid()
{
	CellSize = FVector(100, 100, 100);
	CellCount = FVector(10, 10, 10);
}

// IDEA: only get face of block and block which is hit. then return hitblock.position + facenormal * cellsize
FVector UGrid::GetGridLocationFromWorld(FVector WorldLocation) const
{
	FVector CellLocation;

	CellLocation.X = WorldLocation.X / (CellSize.X);
	CellLocation.Y = WorldLocation.Y / (CellSize.Y);
	CellLocation.Z = WorldLocation.Z / (CellSize.Z);

	CellLocation.X = CellLocation.X < 0.f ? FMath::CeilToInt(CellLocation.X) : FMath::FloorToInt(CellLocation.X);
	CellLocation.Y = CellLocation.Y < 0.f ? FMath::CeilToInt(CellLocation.Y) : FMath::FloorToInt(CellLocation.Y);
	CellLocation.Z = CellLocation.Z < 0.f ? FMath::CeilToInt(CellLocation.Z) : FMath::FloorToInt(CellLocation.Z);

	UE_LOG(LogTemp, Display, TEXT("World: (%.2f | %.2f | %.2f)"), WorldLocation.X, WorldLocation.Y, WorldLocation.Z);
	UE_LOG(LogTemp, Display, TEXT("Cell : (%.2f | %.2f | %.2f)"), CellLocation.X, CellLocation.Y, CellLocation.Z);

	return CellLocation * CellSize;
}
