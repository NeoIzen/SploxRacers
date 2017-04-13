// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "Grid.h"
#include "CarEditorGameState.h"
#include "BasicBlock.h"

UGrid::UGrid() : CellSize(100, 100, 100), CellCount(11, 11, 11)
{
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

bool UGrid::IsValidGridPoint(FVector GridIndex) const
{
	// Convert from [0|x] to [-y|y]
	FVector Min;
	Min = -((CellCount - FVector(1, 1, 1)) / 2);
	Min.X = FMath::CeilToInt(Min.X);
	Min.Y = FMath::CeilToInt(Min.Y);
	Min.Z = FMath::CeilToInt(Min.Z);

	FVector Max;
	Max = (CellCount - FVector(1, 1, 1)) / 2;
	Max.X = FMath::CeilToInt(Max.X);
	Max.Y = FMath::CeilToInt(Max.Y);
	Max.Z = FMath::CeilToInt(Max.Z);

	// Test if grid point is in between min and max
	return ((GridIndex.X >= Min.X) && (GridIndex.X <= Max.X)) && ((GridIndex.Y >= Min.Y) && (GridIndex.Y <= Max.Y)) && ((GridIndex.Z >= Min.Z) && (GridIndex.Z <= Max.Z));
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

void UGrid::RemoveBlockFromGrid(class ABasicBlock* Block)
{
	int64 Hash = HashFromGridPoint(GetGridPointFromWorldLocation(Block->GetActorLocation()));

	ABasicBlock** SavedBlock = Blocks.Find(Hash);

	if(SavedBlock != nullptr && Block == *SavedBlock)
	{
		Blocks.Remove(Hash);
	}
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
