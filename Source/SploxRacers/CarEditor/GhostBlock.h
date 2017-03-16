// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CarEditor/BasicBlock.h"
#include "GhostBlock.generated.h"

/**
 *
 */
UCLASS()
class SPLOXRACERS_API AGhostBlock : public ABasicBlock
{
	GENERATED_BODY()

public:
	AGhostBlock();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Disable();
	void Enable();

	bool IsActive() const;
private:
	bool Enabled;
};
