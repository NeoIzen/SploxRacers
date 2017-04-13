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

	FVector GetGridLocationFromWorldLocation(FVector WorldLocation) const;
	FVector GetGridPointFromWorldLocation(FVector WorldLocation) const;
	FVector GetWorldLocationFromGridPoint(FVector GridIndex) const;

	bool IsValidGridPoint(FVector GridIndex) const;

	bool AddBlockToGrid(class ABasicBlock* Block);
	void RemoveBlockFromGrid(class ABasicBlock* Block);

	static UGrid* GetInstance(AActor* Actor);
private:
	const FVector CellSize;
	const FVector CellCount;

	UPROPERTY()
	TMap<int64, class ABasicBlock*> Blocks;

	int64 HashFromGridPoint(const FVector& GridIndex) const;
};
