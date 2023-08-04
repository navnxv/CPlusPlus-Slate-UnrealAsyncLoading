// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class OOA_API OOASlateLoadingScreen : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(OOASlateLoadingScreen)
	{
	}

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	TSharedPtr<SBorder> LoadingBorder;
	
	FSlateBrush LoadingOuterBrush;

	FSlateBrush LoadingInnerBrush;
	
	FSlateBrush BackgroundBrush;
	
	FSlateBrush ThrobberBrush;
	
	float Time = 0.0f;

	FSlateBrush EmptyBrush;

	uint8 bIsLevelLoaded : 1;
	
	float Opacity = 1.0f;

	UFUNCTION()
	void SetIsLevelLoaded(void IsLoaded);

	UFUNCTION()
	bool GetIsLevelLoaded();
};
