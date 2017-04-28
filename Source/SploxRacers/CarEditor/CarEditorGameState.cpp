// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "CarEditorGameState.h"

ACarEditorGameState::ACarEditorGameState()
{
	Grid = nullptr;
}

UGrid* ACarEditorGameState::GetGrid() const
{
	if(!Grid)
	{
		Grid = NewObject<UGrid>((UObject*)this);
	}

	return Grid;
}
