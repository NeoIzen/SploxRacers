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

	FVector GetGridLocationFromWorldLocation(FVector WorldLocation) const;
	FVector GetGridPointFromWorldLocation(FVector WorldLocation) const;
	FVector GetWorldLocationFromGridPoint(FVector GridIndex) const;

	bool IsValidGridPoint(FVector GridIndex) const;

	void AddStartBlock(TSubclassOf<class UBasicBlock> BlockClass);
	class UBasicBlock* AddBlock(TSubclassOf<class UBasicBlock> BlockClass, FVector const& Location, FRotator const& Rotation, FLinearColor const& Color);
	void RemoveBlock(class UBasicBlock* Block);
	void ClearGrid();

	class UBasicBlock* GetStartBlock() const;

	UFUNCTION(BlueprintCallable, Category = "Grid")
	void SaveToFile(FString Filename);

	UFUNCTION(BlueprintCallable, Category = "Grid")
	void LoadFromFile(FString Filename, bool CreateEditorCollider);

	static const FVector CellSize;
	static const FVector CellCount;
private:
	UPROPERTY(VisibleAnywhere)
	class UBasicBlock* StartBlock;

	UPROPERTY(Instanced, EditAnywhere)
	TMap<uint64, class UBasicBlock*> Blocks;

	uint64 HashFromGridPoint(const FVector& GridIndex) const;
};
