#pragma once

#include "Engine.h"
#include "TrackElementID.generated.h"

UENUM(BlueprintType)
enum class ETrackElementID : uint8
{
	Invalid UMETA(DisplayName = "Invalid"),
	LeftGuardRail UMETA(DisplyName = "Left Guard Rail"),
	RightGuardRail UMETA(DisplyName = "Right Guard Rail"),
	Road UMETA(DisplayName = "Road"),
	Start UMETA(DisplayName = "Start"),
	Speed UMETA(DisplayName = "Speed"),
};