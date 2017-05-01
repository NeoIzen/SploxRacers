// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TrackElementID.h"
#include "UObject/NoExportTypes.h"
#include "TrackGenerator/BasicTrackElement.h"
#include "TrackPartLibrary.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class SPLOXRACERS_API UTrackPartLibrary : public UObject
{
	GENERATED_BODY()
	
public:
	TSubclassOf<ABasicTrackElement> GetTrackPart(ETrackElementID ID) const;
private:
	UPROPERTY(EditAnywhere)
	TMap<ETrackElementID, TSubclassOf<ABasicTrackElement>> TrackPartMap;
};
