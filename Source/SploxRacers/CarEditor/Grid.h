// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "Grid.generated.h"

/**
 *
 */
UCLASS()
class SPLOXRACERS_API UGrid : public UObject
{
	GENERATED_BODY()

public:
	UGrid();

	FVector GetGridLocationFromWorld(FVector WorldLocation) const;
private:
	FVector CellSize;
	FVector CellCount;
};
