// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Grid.h"
#include "BlockLibrary.h"
#include "GameFramework/GameStateBase.h"
#include "CarEditorGameState.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class SPLOXRACERS_API ACarEditorGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ACarEditorGameState();

	UGrid* GetGrid() const;

	UFUNCTION(BlueprintCallable, Category = "Block Library")
	UBlockLibrary* GetBlockLibrary() const;
private:
	UGrid* Grid;
	UBlockLibrary* BlockLibrary;
};
