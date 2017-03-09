// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "CarEditorPawn.generated.h"

UCLASS()
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
private:
	float CameraInput;

	UPROPERTY(EditAnywhere)
	float RotationSpeed;

	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* Camera;

	UPROPERTY()
	class ABasicBlock* StartBlock;
	UPROPERTY()
	class AGhostBlock* GhostBlock;

	void RotateCamera(float AxisValue);
	void PlaceBlock();
};
