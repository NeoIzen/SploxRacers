// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "GhostBlock.h"
#include "BlockLibrary.h"

AGhostBlock::AGhostBlock()
{
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);

	// Set default values
	Enabled = false;
	GhostID = -1;

	GhostingBlock = nullptr;
}

// Called when the game starts or when spawned
void AGhostBlock::BeginPlay()
{
	Super::BeginPlay();
}

void AGhostBlock::Disable()
{
	Enabled = false;
	SetActorHiddenInGame(!Enabled);
}

void AGhostBlock::Enable()
{
	Enabled = true;
	SetActorHiddenInGame(!Enabled);
}

bool AGhostBlock::IsActive() const
{
	return Enabled;
}

void AGhostBlock::SetBlockToGhost(TSubclassOf<UBasicBlock> BlockToGhost)
{
	FLinearColor Color = FLinearColor(1.f, 1.f, 1.f);
	if(GhostingBlock)
	{
		Color = GhostingBlock->GetColor();

		GhostingBlock->DestroyComponent();
	}

	GhostingBlock = NewObject<UBasicBlock>(this, BlockToGhost);
	GhostingBlock->RegisterComponent();
	GhostingBlock->SetColor(Color);
	SetRootComponent(GhostingBlock);
}

UBasicBlock* const AGhostBlock::GetGhostedBlock() const
{
	return GhostingBlock;
}
