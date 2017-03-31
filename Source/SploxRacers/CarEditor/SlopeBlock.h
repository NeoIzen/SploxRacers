// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CarEditor/BasicBlock.h"
#include "SlopeBlock.generated.h"

/**
 * 
 */
UCLASS()
class SPLOXRACERS_API ASlopeBlock : public ABasicBlock
{
	GENERATED_BODY()
	
public:
	ASlopeBlock();

	virtual int32 GetID() const override;
private:
};
