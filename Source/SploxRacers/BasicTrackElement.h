// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BasicTrackElement.generated.h"

UCLASS(abstract)
class SPLOXRACERS_API ABasicTrackElement : public AActor
{
	GENERATED_BODY()

public:
	ABasicTrackElement();

	void SetStartAndEnd(FVector StartPos, FVector StartTangent, FVector EndPos, FVector EndTangent);
	void SetRoll(float StartRoll, float EndRoll);
	void SetScale(FVector2D StartScale, FVector2D EndScale);
protected:
	UPROPERTY(EditDefaultsOnly)
	class USplineMeshComponent* SplineMeshComponent;

	void CreateSplineMeshComponent(UStaticMesh* Mesh);
};
