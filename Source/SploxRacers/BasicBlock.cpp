// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "BasicBlock.h"
#include "Grid.h"

// Sets default values
ABasicBlock::ABasicBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	// Set up collision parameters
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	StaticMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	StaticMeshComponent->SetCollisionObjectType(ECollisionChannel::ECC_Vehicle);
	StaticMeshComponent->SetEnableGravity(false);
	//StaticMeshComponent->SetSimulatePhysics(true);

	RootComponent = StaticMeshComponent;

	// Set defaults
	StaticMesh = nullptr;
	Material = nullptr;

	Tint = FLinearColor(1.f, 1.f, 1.f);
}

// Called when the game starts or when spawned
void ABasicBlock::BeginPlay()
{
	Super::BeginPlay();

	//StaticMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	StaticMeshComponent->SetStaticMesh(StaticMesh);
	UMaterialInstanceDynamic* MaterialInstance = StaticMeshComponent->CreateDynamicMaterialInstance(0, Material);
	StaticMeshComponent->SetMaterial(0, MaterialInstance);
}

void ABasicBlock::SetColor(FLinearColor Color)
{
	UMaterialInstanceDynamic* MaterialInstance = Cast<UMaterialInstanceDynamic>(StaticMeshComponent->GetMaterial(0));

	if(!MaterialInstance)
		return;

	Tint = Color;
	MaterialInstance->SetVectorParameterValue(TEXT("Tint"), Color);
}

FLinearColor ABasicBlock::GetColor() const
{
	return Tint;
}

int32 ABasicBlock::GetID() const
{
	return BlockID;
}

void ABasicBlock::SetID(int32 ID)
{
	BlockID = ID;
}

FBlockProperties ABasicBlock::GetProperties() const
{
	return Properties;
}

void ABasicBlock::SetProperties(const FBlockProperties& Properties)
{
	this->Properties = Properties;
}

void ABasicBlock::SetStaticMesh(UStaticMesh* StaticMesh)
{
	this->StaticMesh = StaticMesh;
}

void ABasicBlock::SetMaterial(UMaterialInterface* Material)
{
	this->Material = Material;
}
