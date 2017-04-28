// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "Grid.h"
#include "SploxRacersGameState.h"
#include "BasicBlock.h"
#include "CarSaveLoad.h"
#include "UtilityLib.h"
#include "FileManager.h"

const FVector UGrid::CellSize = FVector(10, 10, 10);
const FVector UGrid::CellCount = FVector(21, 21, 21);

UGrid::UGrid()
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

void UGrid::SpawnStartBlock(ABasicBlock* Template)
{
	StartBlock = SpawnBlock(Template, GetGridLocationFromWorldLocation(FVector(0.f, 0.f, 0.f)), FRotator(EForceInit::ForceInitToZero), FLinearColor(1.f, 1.f, 1.f));
}

ABasicBlock* UGrid::SpawnBlock(ABasicBlock* Template, FVector const& Location, FRotator const& Rotation, FLinearColor const& Color)
{
	int64 Hash = HashFromGridPoint(GetGridPointFromWorldLocation(Location));

	// Check if cell is already occupied
	if(Blocks.Contains(Hash))
		return nullptr;

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Template = Template;

	ABasicBlock* Block = GetWorld()->SpawnActor<ABasicBlock>(Template->GetClass(), Location, Rotation, SpawnParameters);
	Block->SetColor(Color);

	if(StartBlock)
		//Block->AttachToActor(StartBlock, FAttachmentTransformRules::KeepWorldTransform);
		Block->AttachRootComponentToActor(StartBlock);

	Blocks.Add(Hash, Block);

	return Block;
}

void UGrid::RemoveBlock(class ABasicBlock* Block)
{
	if(Block->GetProperties().Removable)
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

void UGrid::SaveToFile(FString Filename)
{
	// Create binary save
	FBufferArchive ToBinary;

	TArray<ABasicBlock*> Children;
	Blocks.GenerateValueArray(Children);

	Children.Remove(StartBlock);

	CarData Data = CarSaveLoad::CreateCarData(StartBlock, Children);

	CarSaveLoad::SaveLoad(ToBinary, Data);

	// Compress Data
	TArray<uint8> CompressedData;
	FArchiveSaveCompressedProxy Compressor = FArchiveSaveCompressedProxy(CompressedData, ECompressionFlags::COMPRESS_ZLIB);

	Compressor << ToBinary;

	Compressor.Flush();

	// Save to file
	FString SaveDir = UUtilityLib::GetCarPath();
	SaveDir.Append(Filename).Append(UUtilityLib::GetCarExtension());

	FFileHelper::SaveArrayToFile(CompressedData, *SaveDir);
}

class ABasicBlock* UGrid::LoadFromFile(FString Filename)
{
	// Read from file
	FString LoadDir = UUtilityLib::GetCarPath();
	Filename = Filename.Replace(TEXT(".src"), TEXT(""));
	LoadDir.Append(Filename).Append(UUtilityLib::GetCarExtension());

	TArray<uint8> CompressedData;
	if(!FFileHelper::LoadFileToArray(CompressedData, *LoadDir))
	{
		return nullptr;
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
	SpawnStartBlock(BlockLibrary->GetBlock(Data.ID));

	for(CarData ChildData : Data.Children)
	{
		SpawnBlock(BlockLibrary->GetBlock(ChildData.ID),
			ChildData.Transform.GetLocation(), ChildData.Transform.GetRotation().Rotator(),
			ChildData.Color);
	}

	return StartBlock;
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
