// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "CarSaveLoad.h"

CarData CarSaveLoad::CreateCarData(UBasicBlock* ParentBlock, TArray<UBasicBlock*> ChildBlocks)
{
	if(ParentBlock == nullptr)
		return CarData();

	CarData CarData;
	CarData.ID = ParentBlock->GetProperties().BlockID;
	CarData.Color = ParentBlock->GetColor();
	CarData.Transform = ParentBlock->GetComponentTransform();

	for(UBasicBlock* Child : ChildBlocks)
	{
		CarData.Children.Add(CreateCarData(Child, TArray<UBasicBlock*>()));
	}

	return CarData;
}

void CarSaveLoad::SaveLoad(FArchive& Ar, CarData& Data)
{
	Ar << Data;
}
