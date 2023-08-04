// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "LoadingScreenDeveloperSettings.generated.h"

/**
 * 
 */
UCLASS(Config = "Game", DefaultConfig)
class OOA_API ULoadingScreenDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Config, EditAnywhere)
	FSlateBrush LoadingOuterSpinner;

	UPROPERTY(Config, EditAnywhere)
	FSlateBrush LoadingInnerSpinner;
	
	UPROPERTY(Config, EditAnywhere)
	FSlateBrush BackgroundBrush;

	UPROPERTY(Config, EditAnywhere)
	FSlateFontInfo LoadingFont;
	
	UPROPERTY(Config, EditAnywhere)
	FText LoadingText;

	UPROPERTY(Config, EditAnywhere)
	FColor FontColor;

	UPROPERTY(Config, EditAnywhere)
	FSlateBrush ThrobberBrush;

	UPROPERTY(Config, EditAnywhere)
	FSlateBrush BlackScreen;
};

