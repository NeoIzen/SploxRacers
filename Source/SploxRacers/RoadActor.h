// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "RoadData.h"
#include "RoadActor.generated.h"

UCLASS()
class SPLOXRACERS_API ARoadActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARoadActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;
private:
	UPROPERTY(EditDefaultsOnly)
	class USplineComponent* Spline;

	UPROPERTY(EditAnywhere, Category = "Generation")
	TArray<FRoadData> RoadDataArray;

	UPROPERTY(EditAnywhere, Category = "Debug")
	bool DrawTrackPointNumbers;

	void BuildTrackElement(uint32 LoopIndex, TSubclassOf<AActor> InClass);
};
