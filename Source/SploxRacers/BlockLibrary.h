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

	UFUNCTION(BlueprintCallable, Category = "Library")
	TArray<FBlockProperties> GetAllBlocks();

	UFUNCTION(BlueprintCallable, Category = "Library")
	TSubclassOf<UBasicBlock> GetBlock(int32 ID) const;
private:
	UPROPERTY(EditAnywhere)
	TMap<int32, TSubclassOf<UBasicBlock>> BlockMap;
};
