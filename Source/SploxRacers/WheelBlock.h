// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BasicBlock.h"
#include "WheelBlock.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SPLOXRACERS_API UWheelBlock : public UBasicBlock
{
	GENERATED_BODY()
	
public:
	virtual void InitializeWheel();

	UPhysicsConstraintComponent* GetPhysicsConstraintWheel();
protected:
	UPROPERTY(EditAnywhere)
	class UPhysicsConstraintComponent* PhysicsConstraintWheel;
private:
};
