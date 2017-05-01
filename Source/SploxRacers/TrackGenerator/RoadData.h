#pragma once

#include "Engine.h"
#include "TrackElementID.h"
#include "RoadData.generated.h"

USTRUCT()
struct SPLOXRACERS_API FRoadData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	bool LeftRail;

	UPROPERTY(EditAnywhere)
	bool RightRail;

	UPROPERTY(EditAnywhere)
	float TrackBank;

	UPROPERTY(EditAnywhere)
	float TrackWidth;

	UPROPERTY(EditAnywhere)
	float TrackThickness;

	UPROPERTY(EditAnywhere)
	ETrackElementID RoadElementID;

	FRoadData()
	{
		LeftRail = false;
		RightRail = false;
		TrackBank = 0.f;
		TrackWidth = 1.f;
		TrackThickness = 1.f;

		RoadElementID = ETrackElementID::Road;
	}
};