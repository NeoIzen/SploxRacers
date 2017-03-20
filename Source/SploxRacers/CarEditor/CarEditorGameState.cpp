// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "CarEditorGameState.h"

ACarEditorGameState::ACarEditorGameState()
{
	Grid = NewObject<UGrid>();
	BlockLibrary = NewObject<UBlockLibrary>();
}

UGrid* ACarEditorGameState::GetGrid() const
{
	return Grid;
}

UBlockLibrary* ACarEditorGameState::GetBlockLibrary() const
{
	return BlockLibrary;
}
