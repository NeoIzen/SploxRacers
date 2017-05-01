// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "BasicBlock.h"
#include "Grid.h"

// Sets default values
UBasicBlock::UBasicBlock()
{
	PrimaryComponentTick.bCanEverTick = false;

	bAlwaysCreatePhysicsState = true;

	// Set up collision parameters
	SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Ignore);
	SetCollisionObjectType(ECollisionChannel::ECC_Vehicle);
	SetEnableGravity(false);
	SetSimulatePhysics(true);

	// Set defaults
	MaterialInterface = nullptr;

	Tint = FLinearColor(1.f, 1.f, 1.f);
}

// Called when the game starts or when spawned
void UBasicBlock::BeginPlay()
{
	Super::BeginPlay();

	UMaterialInstanceDynamic* MaterialInstance = CreateDynamicMaterialInstance(0, MaterialInterface);
	SetMaterial(0, MaterialInstance);
}

void UBasicBlock::DestroyComponent(bool bPromoteChildren)
{
	Super::DestroyComponent(bPromoteChildren);

	if(GridCollision)
	{
		GridCollision->DestroyComponent();
		GridCollision = nullptr;
	}
}

void UBasicBlock::CreateEditorGridCollision()
{
	// Deactivate own physics
	SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Create grid collider
	GridCollision = NewObject<UBoxComponent>(this);
	GridCollision->SetBoxExtent(UGrid::CellSize / 2.f);
	GridCollision->RegisterComponent();
	GridCollision->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	GridCollision->SetRelativeLocation(FVector::ZeroVector);

	GridCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GridCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
}

void UBasicBlock::SetColor(FLinearColor Color)
{
	UMaterialInstanceDynamic* MaterialInstance = Cast<UMaterialInstanceDynamic>(GetMaterial(0));

	if(!MaterialInstance)
		return;

	Tint = Color;
	MaterialInstance->SetVectorParameterValue(TEXT("Tint"), Color);
}

FLinearColor UBasicBlock::GetColor() const
{
	return Tint;
}

FBlockProperties UBasicBlock::GetProperties() const
{
	return Properties;
}

void UBasicBlock::SetProperties(const FBlockProperties& NewProperties)
{
	Properties = NewProperties;
}

void UBasicBlock::SetMaterialInterface(UMaterialInterface* Material)
{
	MaterialInterface = Material;
}
