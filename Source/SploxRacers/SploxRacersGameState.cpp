// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "SploxRacersGameState.h"

ASploxRacersGameState::ASploxRacersGameState()
{
	BlockLibrary = nullptr;
}

UBlockLibrary* ASploxRacersGameState::GetBlockLibrary() const
{
	if(!BlockLibrary)
	{
		BlockLibrary = NewObject<UBlockLibrary>((UObject*)this, BlockLibraryClass);
		BlockLibrary->Initialize();
	}

	return BlockLibrary;
}
