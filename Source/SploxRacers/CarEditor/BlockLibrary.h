// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "BasicBlock.h"
#include "BlockLibrary.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class SPLOXRACERS_API UBlockLibrary : public UObject
{
	GENERATED_BODY()

public:
	UBlockLibrary();

	static UBlockLibrary* GetInstance(AActor* Actor);

	UFUNCTION(BlueprintImplementableEvent, Category = "Block Library")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Block Library")
	TArray<ABasicBlock*> GetAllBlocks();

	UFUNCTION(BlueprintCallable, Category = "Block Library")
	void AddBlock(TSubclassOf<ABasicBlock> BlockClass);

	UFUNCTION(BlueprintCallable, Category = "Block Library")
	ABasicBlock* GetBlock(int32 ID) const;
private:
	UPROPERTY()
	TMap<int32, ABasicBlock*> BlockMap;
};
