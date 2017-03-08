#pragma once

#include "Engine.h"
#include "RoadData.generated.h"

UENUM(BlueprintType)
enum class FTrackElementID : uint8
{
	Start UMETA(DisplayName = "Start"),
	Road UMETA(DisplayName = "Road"),
	Speed UMETA(DisplayName = "Speed"),
};

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
	FTrackElementID RoadElementID;

	FRoadData()
	{
		LeftRail = false;
		RightRail = false;
		TrackBank = 0.f;
		TrackWidth = 1.f;
		TrackThickness = 1.f;

		RoadElementID = FTrackElementID::Road;
	}
};