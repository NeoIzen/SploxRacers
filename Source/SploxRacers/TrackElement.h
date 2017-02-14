// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BasicTrackElement.h"
#include "TrackElement.generated.h"

/**
 * 
 */
UCLASS()
class SPLOXRACERS_API ATrackElement : public ABasicTrackElement
{
	GENERATED_BODY()
	
public:
	ATrackElement();
private:
	static UStaticMesh* Mesh;
};
