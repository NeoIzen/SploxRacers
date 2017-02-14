// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BasicTrackElement.h"
#include "RightGuardRailElement.generated.h"

/**
 * 
 */
UCLASS()
class SPLOXRACERS_API ARightGuardRailElement : public ABasicTrackElement
{
	GENERATED_BODY()

public:
	ARightGuardRailElement();
private:
	static UStaticMesh* Mesh;
};
