// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "BlockLibrary.h"
#include "CarEditorGameState.h"

UBlockLibrary::UBlockLibrary()
{
}

UBlockLibrary* UBlockLibrary::GetInstance(AActor* Actor)
{
	ACarEditorGameState* GameState = Actor->GetWorld() != nullptr ? Actor->GetWorld()->GetGameState<ACarEditorGameState>() : nullptr;

	return GameState != nullptr ? GameState->GetBlockLibrary() : nullptr;
}

TArray<ABasicBlock*> UBlockLibrary::GetAllBlocks()
{
	TArray<ABasicBlock*> Array;
	BlockMap.GenerateValueArray(Array);

	return Array;
}

void UBlockLibrary::AddBlock(TSubclassOf<ABasicBlock> BlockClass)
{
	ABasicBlock* Block = NewObject<ABasicBlock>(this, BlockClass);
	BlockMap.Emplace(Block->GetID(), Block);
}

ABasicBlock* UBlockLibrary::GetBlock(int32 ID) const
{
	return BlockMap[ID];
}
