// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CarPawnBase.h"
#include "CarEditorPawn.generated.h"

UCLASS()
class SPLOXRACERS_API ACarEditorPawn : public ACarPawnBase
{
	GENERATED_BODY()

public:
	ACarEditorPawn();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Car Editor")
	AGhostBlock* GetGhostBlock();
private:
	UPROPERTY(EditAnywhere)
	int32 StartBlockID;

	// Camera
	FVector2D CameraInput;
	float CameraZoom;

	UPROPERTY(EditAnywhere)
	float RotationSpeed;

	UPROPERTY(EditAnywhere)
	float ZoomSpeed;

	// Actor references
	UPROPERTY()
	class AGhostBlock* GhostBlock;

	// Input handler
	template<int Direction> void RotateCamera(float AxisValue) { RotateCamera(Direction, AxisValue); };
	void RotateCamera(int Direction, float AxisValue);

	void ZoomCamera(float AxisValue);

	template<int Direction> void RotateBlock() { RotateBlock(Direction); };
	void RotateBlock(int Direction);

	void PlaceBlock();
	void RemoveBlock();
};
