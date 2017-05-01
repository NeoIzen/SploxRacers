// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Grid.h"
#include "BlockLibrary.h"
#include "GameFramework/GameStateBase.h"
#include "SploxRacersGameState.generated.h"

/**
 * 
 */
UCLASS()
class SPLOXRACERS_API ASploxRacersGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ASploxRacersGameState();

	UFUNCTION(BlueprintCallable, Category = "Library")
	UBlockLibrary* GetBlockLibrary();

	UPROPERTY(EditAnywhere)
	TSubclassOf<UBlockLibrary> BlockLibraryClass;
private:
	UPROPERTY(Instanced, VisibleAnywhere)
	UBlockLibrary* BlockLibrary;
};
