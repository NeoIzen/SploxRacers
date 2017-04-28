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

	// Set color tint of the material
	UFUNCTION(BlueprintCallable, Category = "Block")
	void SetColor(FLinearColor Color);
	UFUNCTION(BlueprintCallable, Category = "Block")
	FLinearColor GetColor() const;

	UFUNCTION(BlueprintCallable, Category = "Block")
	int32 GetID() const;
	void SetID(int32 ID);

	UFUNCTION(BlueprintCallable, Category = "Block")
	FBlockProperties GetProperties() const;
	void SetProperties(const FBlockProperties& Properties);

	void SetStaticMesh(UStaticMesh* StaticMesh);
	void SetMaterial(UMaterialInterface* Material);
protected:
	UPROPERTY(BlueprintReadWrite)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleDefaultsOnly)
	UBoxComponent* BoxCollider;

	UPROPERTY(VisibleAnywhere)
	FLinearColor Tint;

	UPROPERTY(VisibleAnywhere)
	int32 BlockID;

	UPROPERTY(VisibleAnywhere)
	UStaticMesh* StaticMesh;

	UPROPERTY(VisibleAnywhere)
	UMaterialInterface* Material;

	UPROPERTY(VisibleAnywhere)
	FBlockProperties Properties;
};
