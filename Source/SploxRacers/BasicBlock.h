// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "BlockProperties.h"
#include "BasicBlock.generated.h"

UCLASS(Blueprintable)
class SPLOXRACERS_API UBasicBlock : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UBasicBlock();

	virtual void BeginPlay() override;

	virtual void DestroyComponent(bool bPromoteChildren = false) override;

	void CreateEditorGridCollision();

	// Set color tint of the material
	UFUNCTION(BlueprintCallable, Category = "Block")
	void SetColor(FLinearColor Color);
	UFUNCTION(BlueprintCallable, Category = "Block")
	FLinearColor GetColor() const;

	UFUNCTION(BlueprintCallable, Category = "Block")
	FBlockProperties GetProperties() const;
	void SetProperties(const FBlockProperties& NewProperties);

	void SetMaterialInterface(UMaterialInterface* Material);
protected:
	UPROPERTY(VisibleAnywhere)
	FLinearColor Tint;

	UPROPERTY(VisibleAnywhere)
	UMaterialInterface* MaterialInterface;

	UPROPERTY(EditAnywhere)
	FBlockProperties Properties;

	UPROPERTY(EditAnywhere)
	UBoxComponent* GridCollision;
};
