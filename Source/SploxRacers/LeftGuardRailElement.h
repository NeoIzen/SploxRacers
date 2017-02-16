// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BasicTrackElement.h"
#include "LeftGuardRailElement.generated.h"

/**
 * Left guard rail track element
 */
UCLASS()
class SPLOXRACERS_API ALeftGuardRailElement : public ABasicTrackElement
{
	GENERATED_BODY()

public:
	ALeftGuardRailElement();
private:
	static UStaticMesh* Mesh;
};
