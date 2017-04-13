// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "CarEditorGameState.h"

ACarEditorGameState::ACarEditorGameState()
{
	Grid = nullptr;
	BlockLibrary = nullptr;
}

UGrid* ACarEditorGameState::GetGrid() const
{
	if(!Grid)
	{
		Grid = NewObject<UGrid>();
	}

	return Grid;
}

UBlockLibrary* ACarEditorGameState::GetBlockLibrary() const
{
	if(!BlockLibrary)
	{
		BlockLibrary = NewObject<UBlockLibrary>((UObject*)this, BlockLibraryClass);
		BlockLibrary->Initialize();
	}

	return BlockLibrary;
}
