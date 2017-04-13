// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "CarEditorPawn.generated.h"

UCLASS(BlueprintType)
class SPLOXRACERS_API ACarEditorPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACarEditorPawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Car Editor")
	AGhostBlock* GetGhostBlock();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AGhostBlock> GhostBlockClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABasicBlock> StartBlockClass;
private:
	// Camera values
	FVector2D CameraInput;
	float CameraZoom;

	UPROPERTY(EditAnywhere)
	float RotationSpeed;

	UPROPERTY(EditAnywhere)
	float ZoomSpeed;

	// Components
	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* Camera;

	// Actor references
	UPROPERTY()
	class ABasicBlock* StartBlock;
	UPROPERTY()
	class AGhostBlock* GhostBlock;

	// Input handler
	template<int Direction> void RotateCamera(float AxisValue) { RotateCamera(Direction, AxisValue); };
	void RotateCamera(int Direction, float AxisValue);

	void ZoomCamera(float AxisValue);

	template<int Direction> void RotateBlock() { RotateBlock(Direction); };
	void RotateBlock(int Direction);

	void PlaceBlock();
};
