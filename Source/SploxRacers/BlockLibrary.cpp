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

TArray<FBlockProperties> UBlockLibrary::GetAllBlocks()
{
	TArray<TSubclassOf<UBasicBlock>> Array;
	BlockMap.GenerateValueArray(Array);

	TArray<FBlockProperties> BlockProperties;

	for(TSubclassOf<UBasicBlock> BlockClass : Array)
	{
		BlockProperties.Add(BlockClass->GetDefaultObject<UBasicBlock>()->GetProperties());
	}

	return BlockProperties;
}

TSubclassOf<UBasicBlock> UBlockLibrary::GetBlock(int32 ID) const
{
	const TSubclassOf<UBasicBlock>* Block = BlockMap.Find(ID);

	if(Block == nullptr)
		return TSubclassOf<UBasicBlock>();
	else
		return *Block;
}
