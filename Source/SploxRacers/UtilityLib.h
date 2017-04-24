// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "UtilityLib.generated.h"

/**
 * 
 */
UCLASS()
class SPLOXRACERS_API UUtilityLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	static FString GetCarPath();
	static FString GetCarExtension();

	UFUNCTION(BlueprintCallable, Category = "Utilities")
	static TArray<FString> GetCarNames();
private:
};
