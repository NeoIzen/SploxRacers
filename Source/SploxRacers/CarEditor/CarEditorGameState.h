// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../SploxRacersGameState.h"
#include "CarEditorGameState.generated.h"

/**
 *
 */
UCLASS()
class SPLOXRACERS_API ACarEditorGameState : public ASploxRacersGameState
{
	GENERATED_BODY()

public:
	ACarEditorGameState();

	UFUNCTION(BlueprintCallable, Category = "Block Library")
	UGrid* GetGrid() const;
private:
	UPROPERTY(Instanced, VisibleAnywhere)
	mutable UGrid* Grid;
};
