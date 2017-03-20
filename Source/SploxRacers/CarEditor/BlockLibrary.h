// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "BasicBlock.h"
#include "BlockLibrary.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class SPLOXRACERS_API UBlockLibrary : public UObject
{
	GENERATED_BODY()

public:
	UBlockLibrary();

	UFUNCTION(BlueprintCallable, Category = "Block Library")
	TArray<ABasicBlock*> GetAllBlocks();
private:
	TSet<ABasicBlock*> BlockSet;
};
