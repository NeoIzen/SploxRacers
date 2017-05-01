// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Components/SplineMeshComponent.h"
#include "BasicTrackElement.generated.h"

/*
* Base class for track elements
*/
UCLASS(Blueprintable)
class SPLOXRACERS_API ABasicTrackElement : public AActor
{
	GENERATED_BODY()

public:
	ABasicTrackElement();

	virtual void Initialize();

	virtual void SetStartAndEnd(FVector StartPos, FVector StartTangent, FVector EndPos, FVector EndTangent);
	virtual void SetRoll(float StartRoll, float EndRoll);
	virtual void SetScale(FVector2D StartScale, FVector2D EndScale);
protected:
	UPROPERTY(EditAnywhere)
	UStaticMesh* StaticMesh;

	UPROPERTY()
	USplineMeshComponent* SplineMeshComponent;
};
