// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "SploxRacersGameState.h"

ASploxRacersGameState::ASploxRacersGameState()
{
	BlockLibrary = nullptr;
}

UBlockLibrary* ASploxRacersGameState::GetBlockLibrary()
{
	if(!BlockLibrary)
	{
		BlockLibrary = NewObject<UBlockLibrary>((UObject*)this, BlockLibraryClass);
	}

	return BlockLibrary;
}
