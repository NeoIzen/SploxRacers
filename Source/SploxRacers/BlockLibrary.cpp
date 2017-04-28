// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "BlockLibrary.h"
#include "SploxRacersGameState.h"

UBlockLibrary::UBlockLibrary()
{
}

UBlockLibrary* UBlockLibrary::GetInstance(AActor* Actor)
{
	ASploxRacersGameState* GameState = Actor->GetWorld() != nullptr ? Actor->GetWorld()->GetGameState<ASploxRacersGameState>() : nullptr;

	return GameState != nullptr ? GameState->GetBlockLibrary() : nullptr;
}

TArray<ABasicBlock*> UBlockLibrary::GetAllBlocks()
{
	TArray<ABasicBlock*> Array;
	BlockMap.GenerateValueArray(Array);

	return Array;
}

/*void UBlockLibrary::AddBlock(TSubclassOf<ABasicBlock> BlockClass)
{
	ABasicBlock* Block = NewObject<ABasicBlock>(this, BlockClass);
	BlockMap.Emplace(Block->GetID(), Block);
}*/

void UBlockLibrary::AddBlock(TSubclassOf<ABasicBlock> BaseClass, int32 BlockID, UStaticMesh* Mesh, UMaterialInterface* Material, FBlockProperties Properties)
{
	// Create template
	ABasicBlock* Block = NewObject<ABasicBlock>(this, BaseClass);

	// Set values
	Block->SetID(BlockID);
	Block->SetStaticMesh(Mesh);
	Block->SetMaterial(Material);
	Block->SetProperties(Properties);

	// Add to map
	BlockMap.Emplace(Block->GetID(), Block);
}

ABasicBlock* UBlockLibrary::GetBlock(int32 ID) const
{
	return BlockMap[ID];
}
