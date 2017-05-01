// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "CarPawnBase.h"
#include "Grid.h"

ACarPawnBase::ACarPawnBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Grid = nullptr;
}

USpringArmComponent* ACarPawnBase::GetSpringArmComponent()
{
	return SpringArm;
}

UGrid* ACarPawnBase::GetGrid()
{
	if(!Grid)
	{
		Grid = NewObject<UGrid>((UObject*)this);
	}

	return Grid;
}

void ACarPawnBase::BeginPlay()
{
	Super::BeginPlay();
	
}
