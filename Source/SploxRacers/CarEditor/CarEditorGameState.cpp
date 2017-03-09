// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "CarEditorGameState.h"

ACarEditorGameState::ACarEditorGameState()
{
	Grid = NewObject<UGrid>();
}

UGrid* ACarEditorGameState::GetGrid() const
{
	return Grid;
}
