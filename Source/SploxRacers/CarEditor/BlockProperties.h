#pragma once

#include "Engine.h"
#include "BlockProperties.generated.h"

USTRUCT(BlueprintType)
struct SPLOXRACERS_API FBlockProperties
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString BlockName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Weight; // kg

	FBlockProperties()
	{
		BlockName = TEXT("INVALID BLOCK NAME");
		Weight = 1.f;
	}
};
