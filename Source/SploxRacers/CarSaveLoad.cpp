// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "CarSaveLoad.h"

/*CarData CarSaveLoad::CreateCarData(ABasicBlock* Block)
{
	if(Block == nullptr)
		return CarData();

	CarData Car;
	Car.ID = Block->BlockID;
	Car.Color = Block->GetColor();
	Car.Transform = Block->GetActorTransform();

	for(USceneComponent* ChildComponent : Block->GetDefaultAttachComponent()->GetAttachChildren())
	{
		AActor* ChildBlock = ChildComponent->GetOwner();
		Car.Children.Add(CreateCarData(Cast<ABasicBlock>(ChildBlock)));
	}

	return Car;
}*/

CarData CarSaveLoad::CreateCarData(ABasicBlock* ParentBlock, TArray<ABasicBlock*> ChildBlocks)
{
	if(ParentBlock == nullptr)
		return CarData();

	CarData CarData;
	CarData.ID = ParentBlock->BlockID;
	CarData.Color = ParentBlock->GetColor();
	CarData.Transform = ParentBlock->GetActorTransform();

	for(ABasicBlock* Child : ChildBlocks)
	{
		CarData.Children.Add(CreateCarData(Child, TArray<ABasicBlock*>()));
	}

	return CarData;
}

void CarSaveLoad::SaveLoad(FArchive& Ar, CarData& Data)
{
	Ar << Data;
}
