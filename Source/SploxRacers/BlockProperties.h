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
	FString Category;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Weight; // kg

	UPROPERTY(EditAnywhere)
	bool Removable;

	FBlockProperties()
	{
		BlockName = TEXT("INVALID BLOCK NAME");
		Category = TEXT("");
		Weight = 1.f;
		Removable = true;
	}
};
