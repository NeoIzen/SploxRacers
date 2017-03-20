// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "BasicBlock.h"
#include "Grid.h"

// Sets default values
ABasicBlock::ABasicBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Set up hirarchy
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = StaticMeshComponent;
	StaticMeshComponent->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Engine/BasicShapes/Cube.Cube")).Object);
	StaticMeshComponent->SetMaterial(0, ConstructorHelpers::FObjectFinder<UMaterialInterface>(TEXT("/Game/Materials/CarEditor/Block.Block")).Object);
	StaticMeshComponent->SetMobility(EComponentMobility::Movable);

	// Ignore camera collision
	StaticMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	// Set properties
	Properties.BlockName = "Chassis Full Block";
	Properties.Weight = 10.f;
}

// Called when the game starts or when spawned
void ABasicBlock::BeginPlay()
{
	Super::BeginPlay();

	Material = StaticMeshComponent->CreateAndSetMaterialInstanceDynamic(0);
}

void ABasicBlock::SetColor(float r, float g, float b)
{
	Material->SetVectorParameterValue(TEXT("Tint"), FLinearColor(r, g, b));
}

void ABasicBlock::OnSpawn()
{
	UGrid::GetInstance(this)->AddBlockToGrid(this);
}

FBlockProperties ABasicBlock::GetProperties() const
{
	return Properties;
}
