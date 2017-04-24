// Fill out your copyright notice in the Description page of Project Settings.

#include "SploxRacers.h"
#include "UtilityLib.h"
#include "FileManager.h"

FString UUtilityLib::GetCarPath()
{
	return FPaths::GameDir().Append(TEXT("Cars/"));
}

FString UUtilityLib::GetCarExtension()
{
	return TEXT(".src");
}

TArray<FString> UUtilityLib::GetCarNames()
{
	IFileManager& FileManager = IFileManager::Get();

	if(!FileManager.DirectoryExists(*GetCarPath()))
		return TArray<FString>();

	TArray<FString> CarNames;

	FileManager.FindFiles(CarNames, *GetCarPath(), *GetCarExtension());

	return CarNames;
}
