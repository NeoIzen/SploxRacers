// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "Grid.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class SPLOXRACERS_API UGrid : public UObject
{
	GENERATED_BODY()

public:
	UGrid();

	class UWorld* GetWorld() const override;

	FVector GetGridLocationFromWorldLocation(FVector WorldLocation) const;
	FVector GetGridPointFromWorldLocation(FVector WorldLocation) const;
	FVector GetWorldLocationFromGridPoint(FVector GridIndex) const;

	bool IsValidGridPoint(FVector GridIndex) const;

	void SpawnStartBlock(class ABasicBlock* Template);
	class ABasicBlock* SpawnBlock(class ABasicBlock* Template, FVector const& Location, FRotator const& Rotation, FLinearColor const& Color);
	void RemoveBlock(class ABasicBlock* Block);
	void ClearGrid();

	UFUNCTION(BlueprintCallable, Category = "Grid")
	void SaveToFile(FString Filename);

	UFUNCTION(BlueprintCallable, Category = "Grid")
	class ABasicBlock* LoadFromFile(FString Filename);

	static const FVector CellSize;
	static const FVector CellCount;
private:
	UPROPERTY(VisibleAnywhere)
	class ABasicBlock* StartBlock;

	UPROPERTY(VisibleAnywhere)
	TMap<uint64, class ABasicBlock*> Blocks;

	uint64 HashFromGridPoint(const FVector& GridIndex) const;
};
