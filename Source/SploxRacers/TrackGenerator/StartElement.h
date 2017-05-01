// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BasicTrackElement.h"
#include "StartElement.generated.h"

/**
 * Track element for the start of the track.
 */
UCLASS(Blueprintable)
class SPLOXRACERS_API AStartElement : public ABasicTrackElement
{
	GENERATED_BODY()

public:
	AStartElement();

	virtual void Initialize() override;

	void SetStartAndEnd(FVector StartPos, FVector StartTangent, FVector EndPos, FVector EndTangent) override;
	void SetRoll(float StartRoll, float EndRoll) override;
	void SetScale(FVector2D StartScale, FVector2D EndScale) override;
protected:
	UPROPERTY()
	UBoxComponent* TriggerArea;

	UPROPERTY()
	UDecalComponent* Decal;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* DecalMaterial;
};
