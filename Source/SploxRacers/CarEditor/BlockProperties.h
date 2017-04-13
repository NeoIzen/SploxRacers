#pragma once

#include "Engine.h"
#include "BlockProperties.generated.h"

USTRUCT(BlueprintType)
struct SPLOXRACERS_API FBlockProperties
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString BlockName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Weight; // kg

	FBlockProperties()
	{
		BlockName = TEXT("INVALID BLOCK NAME");
		Weight = 1.f;
	}
};
