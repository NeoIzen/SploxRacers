// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BasicBlock.h"

struct CarData
{
	int32 ID;

	FLinearColor Color;

	FTransform Transform;

	TArray<CarData> Children;
};

FORCEINLINE FArchive& operator<<(FArchive& Ar, CarData& Data)
{
	//if(!Data) return Ar;

	Ar << Data.ID;
	Ar << Data.Color;
	Ar << Data.Transform;
	Ar << Data.Children;

	return Ar;
}

/**
 * 
 */
class SPLOXRACERS_API CarSaveLoad
{
public:
	static CarData CreateCarData(ABasicBlock* StartBlock, TArray<ABasicBlock*> ChildBlocks);

	static void SaveLoad(FArchive& Ar, CarData& Data);
};
