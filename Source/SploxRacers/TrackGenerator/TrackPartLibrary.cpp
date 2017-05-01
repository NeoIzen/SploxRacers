// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "TrackPartLibrary.h"

TSubclassOf<ABasicTrackElement> UTrackPartLibrary::GetTrackPart(ETrackElementID ID) const
{
	const TSubclassOf<ABasicTrackElement>* Subclass = TrackPartMap.Find(ID);

	if(Subclass == nullptr)
		return TSubclassOf<ABasicTrackElement>();
	else
		return *Subclass;
}
