#pragma once

#include "Engine.h"
#include "BlockProperties.generated.h"

USTRUCT(BlueprintType)
struct SPLOXRACERS_API FBlockProperties
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString BlockName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Category;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Weight; // kg

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Removable;

	FBlockProperties()
	{
		BlockName = TEXT("INVALID BLOCK NAME");
		Category = TEXT("");
		Weight = 1.f;
		Removable = true;
	}
};
