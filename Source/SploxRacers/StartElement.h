// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BasicTrackElement.h"
#include "StartElement.generated.h"

/**
 * 
 */
UCLASS()
class SPLOXRACERS_API AStartElement : public ABasicTrackElement
{
	GENERATED_BODY()

public:
	AStartElement();
private:
	static UStaticMesh* Mesh;
};
