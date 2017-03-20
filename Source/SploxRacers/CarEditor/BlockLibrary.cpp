// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "BlockLibrary.h"
#include "SlopeBlock.h"

UBlockLibrary::UBlockLibrary()
{
	BlockSet.Add(CreateDefaultSubobject<ABasicBlock>(TEXT("BasicBlock")));
	BlockSet.Add(CreateDefaultSubobject<ASlopeBlock>(TEXT("SlopeBlock")));
}

TArray<class ABasicBlock*> UBlockLibrary::GetAllBlocks()
{
	return BlockSet.Array();
}
