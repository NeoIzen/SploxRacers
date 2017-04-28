// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WheeledVehicle.h"
#include "VehiclePawn.generated.h"

/**
 * 
 */
UCLASS()
class SPLOXRACERS_API AVehiclePawn : public APawn
{
	GENERATED_BODY()
	
public:
	AVehiclePawn(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "Splox Racers")
	class UGrid* GetGrid();

	UFUNCTION(BlueprintCallable, Category = "Splox Racers")
	void Initialize(class ABasicBlock* ParentBlock);


	void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	void Tick(float Delta) override;
private:
	UPROPERTY()
	class UGrid* Grid;

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly)
	UBoxComponent* Box;

	UPROPERTY(Category = Camera, VisibleDefaultsOnly)
	USpringArmComponent* SpringArm;

	UPROPERTY(Category = Camera, VisibleDefaultsOnly)
	UCameraComponent* Camera;

	UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UWheeledVehicleMovementComponent* VehicleMovement;

	class UWheeledVehicleMovementComponent* GetVehicleMovementComponent() const;

	// Input delegates
	void Throttle(float Val);
	void Steer(float Val);

	template<bool Pressed> void Handbrake() { Handbrake(Pressed); };
	void Handbrake(bool Pressed);
};
