// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "RoadData.h"
#include "RoadActor.generated.h"

/*
* Actor to build the entire racing track
*/
UCLASS()
class SPLOXRACERS_API ARoadActor : public AActor
{
	GENERATED_BODY()

public:
	ARoadActor();
private:
	UPROPERTY(EditDefaultsOnly)
	class USplineComponent* Spline;

	UPROPERTY(EditAnywhere, Category = "Generation")
	TArray<FRoadData> RoadDataArray;

	UPROPERTY(EditAnywhere, Category = "Debug")
	bool DrawTrackPointNumbers;

	UPROPERTY()
	TArray<UChildActorComponent*> ChildActors;

	virtual void OnConstruction(const FTransform& Transform) override;

	void SetStartValues();
	void BuildTrackElement(uint32 LoopIndex, TSubclassOf<AActor> InClass);
};
