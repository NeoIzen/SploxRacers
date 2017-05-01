// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CarPawnBase.h"
#include "CarPawn.generated.h"

/**
 * 
 */
UCLASS()
class SPLOXRACERS_API ACarPawn : public ACarPawnBase
{
	GENERATED_BODY()
	
public:
	ACarPawn();

	UFUNCTION(BlueprintCallable, Category = "Splox Racers")
	void Initialize(class ARoadActor* Road);

	void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	void Tick(float Delta) override;
private:
	void SetupWheels();

	UPROPERTY()
	TArray<class UWheelBlock*> Wheels;

	// Input delegates
	void Throttle(float Val);
	void Steer(float Val);

	template<bool Pressed> void Handbrake() { Handbrake(Pressed); };
	void Handbrake(bool Pressed);
};
