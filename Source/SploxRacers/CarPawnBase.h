// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "CarPawnBase.generated.h"

UCLASS()
class SPLOXRACERS_API ACarPawnBase : public APawn
{
	GENERATED_BODY()

public:
	ACarPawnBase();

	USpringArmComponent* GetSpringArmComponent();

	UFUNCTION(BlueprintCallable, Category = "Library")
	class UGrid* GetGrid();
protected:
	UPROPERTY(Category = Camera, VisibleDefaultsOnly)
	USpringArmComponent* SpringArm;

	UPROPERTY(Category = Camera, VisibleDefaultsOnly)
	UCameraComponent* Camera;

	UPROPERTY(Instanced, VisibleAnywhere)
	class UGrid* Grid;

	void BeginPlay() override;
};
