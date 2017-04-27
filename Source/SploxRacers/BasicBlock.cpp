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
	RootComponent = StaticMeshComponent;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	BoxCollider->SetBoxExtent(FVector(5, 5, 5));
	BoxCollider->SetRelativeLocation(FVector::ZeroVector);

	StaticMesh = nullptr;
	Material = nullptr;

	Tint = FLinearColor(1.f, 1.f, 1.f);

	// Set properties
	Properties.BlockName = "Chassis Full Block";
	Properties.Weight = 10.f;
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

FBlockProperties ABasicBlock::GetProperties() const
{
	return Properties;
}