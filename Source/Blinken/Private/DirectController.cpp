// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "BlinkenPrivatePCH.h"
#include "DirectController.h"

#define CHANGE_FREQUENCY 0.05f

FDirectController::FDirectController() : FBaseController()
{	
}

void FDirectController::SetGlobalColor(const FColor color)
{
	if (!bEnabled)
	{
		return;
	}

	// clear any flash effects
	targetColor = color;
	targetTimeLeft = 0;
	targetDuration = 0;

	FBaseController::SetGlobalColor(color);
}

void FDirectController::FlashColor(FColor color, float duration)
{
	if (!bEnabled)
	{
		return;
	}

	targetColor = color;
	targetTimeLeft = duration;
	targetDuration = duration;

	// Tick() takes care of actually setting the appropriate color over time, but go ahead and do the first set now
	ProcessFlash();
}

void FDirectController::Tick(float DeltaTime)
{
	if (!bEnabled)
	{
		return;
	}

	accumulatedTime += DeltaTime;

	if (accumulatedTime < CHANGE_FREQUENCY)
	{
		return;
	}

	if (targetTimeLeft > 0.0f)
	{
		ProcessFlash(accumulatedTime);
	}

	accumulatedTime = 0.0f;
}

void FDirectController::ProcessFlash(const float deltaTime)
{
	float progressToGlobalColor = 1.0f - (targetTimeLeft / targetDuration);
	FColor currentColor;

	/*
	currentColor.R = FMath::Lerp(targetColor.R, globalColor.R, progressToGlobalColor);
	currentColor.G = FMath::Lerp(targetColor.G, globalColor.G, progressToGlobalColor);
	currentColor.B = FMath::Lerp(targetColor.B, globalColor.B, progressToGlobalColor);
	*/

	/*
	currentColor.R = FMath::InterpEaseIn(targetColor.R, globalColor.R, progressToGlobalColor, 0.5);
	currentColor.G = FMath::InterpEaseIn(targetColor.G, globalColor.G, progressToGlobalColor, 0.5);
	currentColor.B = FMath::InterpEaseIn(targetColor.B, globalColor.B, progressToGlobalColor, 0.5);
	*/

	currentColor.R = FMath::InterpEaseOut(targetColor.R, globalColor.R, progressToGlobalColor, 0.4);
	currentColor.G = FMath::InterpEaseOut(targetColor.G, globalColor.G, progressToGlobalColor, 0.4);
	currentColor.B = FMath::InterpEaseOut(targetColor.B, globalColor.B, progressToGlobalColor, 0.4);

	targetTimeLeft -= deltaTime;

	if (targetTimeLeft <= 0.0f)
	{
		currentColor = globalColor;
	}

	SetCurrentColor(currentColor);
}
