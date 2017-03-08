// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "CarEditorGameMode.h"
#include "CarEditorGameState.h"
#include "CarEditorPawn.h"

ACarEditorGameMode::ACarEditorGameMode()
{
	GameStateClass = ACarEditorGameState::StaticClass();
	DefaultPawnClass = ACarEditorPawn::StaticClass();
}
