// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "BlockLibrary.h"
#include "CarEditorGameState.h"
#include "SlopeBlock.h"

UBlockLibrary::UBlockLibrary()
{
	AddBlock<ABasicBlock>(TEXT("BasicBlock"));
	AddBlock<ASlopeBlock>(TEXT("SlopeBlock"));
}

TArray<class ABasicBlock*> UBlockLibrary::GetAllBlocks()
{
	TArray<class ABasicBlock*> Array;
	BlockMap.GenerateValueArray(Array);

	return Array;
}

ABasicBlock* UBlockLibrary::GetBlock(int32 ID) const
{
	return BlockMap[ID];
}

UBlockLibrary* UBlockLibrary::GetInstance(AActor* Actor)
{
	ACarEditorGameState* GameState = Actor->GetWorld() != nullptr ? Actor->GetWorld()->GetGameState<ACarEditorGameState>() : nullptr;

	return GameState != nullptr ? GameState->GetBlockLibrary() : nullptr;
}
