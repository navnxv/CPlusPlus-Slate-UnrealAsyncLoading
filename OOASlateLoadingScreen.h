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

	bool bIsLevelLoaded = false;
	float Opacity = 1.0f;
};
