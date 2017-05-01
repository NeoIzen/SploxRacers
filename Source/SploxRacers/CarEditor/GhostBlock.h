// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BasicBlock.h"
#include "GhostBlock.generated.h"

/**
 *
 */
UCLASS()
class SPLOXRACERS_API AGhostBlock : public AActor
{
	GENERATED_BODY()

public:
	AGhostBlock();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Disable();
	void Enable();

	bool IsActive() const;

	UFUNCTION(BlueprintCallable, Category = "Ghost Block")
	void SetBlockToGhost(TSubclassOf<UBasicBlock> BlockToGhost);

	UFUNCTION(BlueprintCallable, Category = "Ghost Block")
	UBasicBlock* const GetGhostedBlock() const;
private:
	bool Enabled;
	int32 GhostID;

	UPROPERTY(VisibleAnywhere)
	UBasicBlock* GhostingBlock;
};
