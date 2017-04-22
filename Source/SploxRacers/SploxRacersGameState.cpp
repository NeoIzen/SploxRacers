// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "SploxRacersGameState.h"

ASploxRacersGameState::ASploxRacersGameState()
{
	Grid = nullptr;
	BlockLibrary = nullptr;
}

UGrid* ASploxRacersGameState::GetGrid() const
{
	if(!Grid)
	{
		Grid = NewObject<UGrid>((UObject*)this);
	}

	return Grid;
}

UBlockLibrary* ASploxRacersGameState::GetBlockLibrary() const
{
	if(!BlockLibrary)
	{
		BlockLibrary = NewObject<UBlockLibrary>((UObject*)this, BlockLibraryClass);
		BlockLibrary->Initialize();
	}

	return BlockLibrary;
}
