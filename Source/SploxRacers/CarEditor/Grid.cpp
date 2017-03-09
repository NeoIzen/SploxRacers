// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "Grid.h"
#include "CarEditorGameState.h"
#include "BasicBlock.h"

UGrid::UGrid()
{
	CellSize = FVector(100, 100, 100);
	CellCount = FVector(10, 10, 10);
}

FVector UGrid::GetGridLocationFromWorldLocation(FVector WorldLocation) const
{
	return GetGridPointFromWorldLocation(WorldLocation) * CellSize;
}

FVector UGrid::GetGridPointFromWorldLocation(FVector WorldLocation) const
{
	auto Round = [](float val) -> int32
	{
		if(val < 0.0f)
			return static_cast<int32>(val - 0.5f + 0.0001f);
		else
			return static_cast<int32>(val + 0.5f - 0.0001f);
	};

	FVector CellID;

	CellID.X = Round(WorldLocation.X / (CellSize.X));
	CellID.Y = Round(WorldLocation.Y / (CellSize.Y));
	CellID.Z = Round(WorldLocation.Z / (CellSize.Z));

	return CellID;
}

FVector UGrid::GetWorldLocationFromGridPoint(FVector GridIndex) const
{
	return GridIndex * CellSize;
}

bool UGrid::AddBlockToGrid(ABasicBlock* Block)
{
	int64 Hash = HashFromGridPoint(GetGridPointFromWorldLocation(Block->GetActorLocation()));

	// Check if cell is already occupied
	if(Blocks.Contains(Hash))
		return false;

	Blocks.Add(Hash, Block);

	return true;
}

UGrid* UGrid::GetInstance(AActor* Actor)
{
	ACarEditorGameState* GameState = Actor->GetWorld() != nullptr ? Actor->GetWorld()->GetGameState<ACarEditorGameState>() : nullptr;

	return GameState != nullptr? GameState->GetGrid() : nullptr;
}

int64 UGrid::HashFromGridPoint(const FVector& GridIndex) const
{
	int16 X = GridIndex.X;
	int16 Y = GridIndex.Y;
	int16 Z = GridIndex.Z;

	int64 Hash = 0;
	Hash |= Z;
	Hash <<= 16;
	Hash |= Y;
	Hash <<= 16;
	Hash |= X;

	return Hash;
}
