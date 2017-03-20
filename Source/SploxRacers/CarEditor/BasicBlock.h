// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BlockProperties.h"
#include "BasicBlock.generated.h"

UCLASS(BlueprintType)
class SPLOXRACERS_API ABasicBlock : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABasicBlock();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// How many grid cells are occupied by this TODO: determine return type
	void GridDimensions();

	// Set color tint of the material
	void SetColor(float r, float g, float b);

	void OnSpawn();

	UFUNCTION(BlueprintCallable, Category = "Block Library")
	FBlockProperties GetProperties() const;
protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY()
	UMaterialInstanceDynamic* Material;

	UPROPERTY(VisibleAnywhere)
	FBlockProperties Properties;
};
