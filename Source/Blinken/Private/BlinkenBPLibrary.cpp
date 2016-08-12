// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "BlinkenPrivatePCH.h"
#include "BlinkenBPLibrary.h"
#include "RazerChromaController.h"

UBlinkenBPLibrary::UBlinkenBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

void UBlinkenBPLibrary::SetGlobalColor(FColor color)
{
	FRazerChromaController::Get()->SetGlobalColor(color);
	FLogitechGLEDController::Get()->SetGlobalColor(color);
	FAlienFXController::Get()->SetGlobalColor(color);
}

void UBlinkenBPLibrary::FlashColor(FColor color, int durationMS)
{
	// TODO FRazerChromaController::Get()->FlashColor(color, durationMS);
	FLogitechGLEDController::Get()->FlashColor(color, durationMS);
	// TODO FAlienFXController::Get()->FlashColor(color, durationMS);
}