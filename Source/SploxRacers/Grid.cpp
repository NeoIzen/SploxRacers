// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "Grid.h"
#include "SploxRacersGameState.h"
#include "BasicBlock.h"
#include "CarSaveLoad.h"
#include "FileManager.h"

UGrid::UGrid() : CellSize(100, 100, 100), CellCount(11, 11, 11)
{
}

class UWorld* UGrid::GetWorld() const
{
	return Cast<AGameStateBase>(GetOuter())->GetWorld();
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

bool UGrid::SpawnBlock(UClass* Class, FVector const& Location, FRotator const& Rotation, FLinearColor const& Color)
{
	int64 Hash = HashFromGridPoint(GetGridPointFromWorldLocation(Location));

	// Check if cell is already occupied
	if(Blocks.Contains(Hash))
		return false;

	ABasicBlock* Block = GetWorld()->SpawnActor<ABasicBlock>(Class, Location, Rotation);
	Block->AttachToActor(StartBlock, FAttachmentTransformRules::KeepWorldTransform);
	Block->SetColor(Color);

	Blocks.Add(Hash, Block);

	return true;
}

void UGrid::RemoveBlock(class ABasicBlock* Block)
{
	if(Block->Properties.Removable)
	{
		int64 Hash = HashFromGridPoint(GetGridPointFromWorldLocation(Block->GetActorLocation()));

		ABasicBlock** SavedBlock = Blocks.Find(Hash);

		if(SavedBlock != nullptr && Block == *SavedBlock)
		{
			Blocks.Remove(Hash);
			Block->Destroy();
		}
	}
}

void UGrid::ClearGrid()
{
	for(auto Block : Blocks)
	{
		Blocks.Remove(Block.Key);
		Block.Value->Destroy();
	}
}

void UGrid::SpawnStartBlock(TSubclassOf<class ABasicBlock> StartBlockClass)
{
	StartBlock = GetWorld()->SpawnActor<ABasicBlock>(StartBlockClass, GetGridLocationFromWorldLocation(FVector(0.f, 0.f, 0.f)), FRotator(EForceInit::ForceInitToZero));

	Blocks.Add(HashFromGridPoint(GetGridPointFromWorldLocation(FVector(0.f, 0.f, 0.f))), StartBlock);
}

UGrid* UGrid::GetInstance(AActor* Actor)
{
	ASploxRacersGameState* GameState = Actor->GetWorld() != nullptr ? Actor->GetWorld()->GetGameState<ASploxRacersGameState>() : nullptr;

	return GameState != nullptr? GameState->GetGrid() : nullptr;
}

void UGrid::SaveToFile(FString Filename)
{
	// Create binary save
	FBufferArchive ToBinary;

	CarData Data = CarSaveLoad::CreateCarData(*Blocks.Find(HashFromGridPoint(GetGridPointFromWorldLocation(FVector(0, 0, 0)))));

	CarSaveLoad::SaveLoad(ToBinary, Data);

	// Compress Data
	TArray<uint8> CompressedData;
	FArchiveSaveCompressedProxy Compressor = FArchiveSaveCompressedProxy(CompressedData, ECompressionFlags::COMPRESS_ZLIB);

	Compressor << ToBinary;

	Compressor.Flush();

	// Save to file
	FString SaveDir = FPaths::GameDir().Append(TEXT("Cars/"));
	SaveDir.Append(Filename).Append(TEXT(".src"));

	FFileHelper::SaveArrayToFile(CompressedData, *SaveDir);
}

void UGrid::LoadFromFile(FString Filename)
{
	// Read from file
	FString LoadDir = FPaths::GameDir().Append(TEXT("Cars/"));
	LoadDir.Append(Filename).Append(TEXT(".src"));

	TArray<uint8> CompressedData;
	if(!FFileHelper::LoadFileToArray(CompressedData, *LoadDir))
	{
		return;
	}

	// Decompress data
	FArchiveLoadCompressedProxy Decompressor = FArchiveLoadCompressedProxy(CompressedData, ECompressionFlags::COMPRESS_ZLIB);

	FBufferArchive DecompressedBinaryArray;
	Decompressor << DecompressedBinaryArray;

	FMemoryReader FromBinary = FMemoryReader(DecompressedBinaryArray, true);
	FromBinary.Seek(0);

	CarData Data;
	CarSaveLoad::SaveLoad(FromBinary, Data);

	// Build grid
	ClearGrid();

	// Spawn all blocks
	UBlockLibrary* BlockLibrary = Cast<ASploxRacersGameState>(GetOuter())->GetBlockLibrary();
	SpawnStartBlock(BlockLibrary->GetBlock(Data.ID)->GetClass());

	for(CarData ChildData : Data.Children)
	{
		SpawnBlock(BlockLibrary->GetBlock(ChildData.ID)->GetClass(),
			ChildData.Transform.GetLocation(), ChildData.Transform.GetRotation().Rotator(),
			ChildData.Color);
	}
}

uint64 UGrid::HashFromGridPoint(const FVector& GridIndex) const
{
	uint16 X = GridIndex.X;
	uint16 Y = GridIndex.Y;
	uint16 Z = GridIndex.Z;

	uint64 Hash = 0;
	Hash |= Z;
	Hash <<= 16;
	Hash |= Y;
	Hash <<= 16;
	Hash |= X;

	return std::hash<uint64>{}(Hash);
}
