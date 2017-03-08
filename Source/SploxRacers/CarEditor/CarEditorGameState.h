// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameStateBase.h"
#include "Grid.h"
#include "CarEditorGameState.generated.h"

/**
 *
 */
UCLASS()
class SPLOXRACERS_API ACarEditorGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ACarEditorGameState();

	UGrid const* GetGrid() const;
private:
	UGrid const* Grid;
};
