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
	UFUNCTION(BlueprintCallable, Category = "Block")
	void SetColor(FLinearColor color);
	FLinearColor GetColor() const;

	void OnSpawn();

	UStaticMeshComponent* GetStaticMeshComponent() const;

	UFUNCTION(BlueprintCallable, Category = "Block")
	virtual int32 GetID() const;

	UFUNCTION(BlueprintCallable, Category = "Block")
	FBlockProperties GetProperties() const;
protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY()
	UMaterialInstanceDynamic* Material;

	UPROPERTY(VisibleAnywhere)
	FBlockProperties Properties;
};
