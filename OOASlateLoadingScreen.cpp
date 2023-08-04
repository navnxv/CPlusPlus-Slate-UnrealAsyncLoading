// Fill out your copyright notice in the Description page of Project Settings.


#include "OOASlateLoadingScreen.h"

#include "LoadingScreenDeveloperSettings.h"
#include "MoviePlayer.h"
#include "SlateOptMacros.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "OOA/Utils/CustomUtils.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Images/SThrobber.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void OOASlateLoadingScreen::Construct(const FArguments& InArgs)
{
	const ULoadingScreenDeveloperSettings* Settings = GetDefault<ULoadingScreenDeveloperSettings>();
	if(!IsValid(Settings)) return;

	LoadingOuterBrush = Settings->LoadingOuterSpinner;
	if(!IsValid(LoadingOuterBrush.GetResourceObject())) return;

	LoadingInnerBrush = Settings->LoadingInnerSpinner;
	if(!IsValid(LoadingInnerBrush.GetResourceObject())) return;
	
	BackgroundBrush = Settings->BackgroundBrush;
	if(!IsValid(BackgroundBrush.GetResourceObject())) return;

	ThrobberBrush = Settings->ThrobberBrush;
	if(!IsValid(ThrobberBrush.GetResourceObject())) return;

	EmptyBrush = Settings->BlackScreen;
	if(!IsValid(EmptyBrush.GetResourceObject())) return;

	const FSlateFontInfo LoadingFont = Settings->LoadingFont;
	
	const FText LoadingText = Settings->LoadingText;

	ChildSlot[
		SNew(SOverlay)
		+SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SImage)
			.Image(&BackgroundBrush)
		]
		+SOverlay::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(SImage)
			.Image(&LoadingOuterBrush)
		]
		+SOverlay::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(SImage)
			.Image(&LoadingInnerBrush)
		]
		+SOverlay::Slot()
		.HAlign(HAlign_Right)
		.VAlign(VAlign_Bottom)
		.Padding(10.0f)
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.AutoWidth()
			[
				
				SNew(STextBlock)
				.Text(LoadingText)
				.Font(LoadingFont)
				.ColorAndOpacity(Settings->FontColor)
			]
		
			+SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SThrobber)
				.PieceImage(&ThrobberBrush)
				.RenderTransform(FVector2D(0.0f, 70.0f))
			]
		]
		+SOverlay::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(SImage)
			.Image(&EmptyBrush)
		]
	];
}

void OOASlateLoadingScreen::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime,
	const float InDeltaTime)
{
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);

	Time += InDeltaTime;
	
	UMaterialInstanceDynamic* MID = UWidgetBlueprintLibrary::GetDynamicMaterial(LoadingOuterBrush);
	UMaterialInstanceDynamic* MID2 = UWidgetBlueprintLibrary::GetDynamicMaterial(LoadingInnerBrush);
	UMaterialInstanceDynamic* EmptyScreenMID = UWidgetBlueprintLibrary::GetDynamicMaterial(EmptyBrush);
	
	if(IsValid(MID) && IsValid(MID2) && IsValid(EmptyScreenMID))
	{
		MID->SetScalarParameterValue(FName(TEXT("Time")), Time);
		MID2->SetScalarParameterValue(FName(TEXT("Time")), Time);

		if(Time < 1.0)
		{
			EmptyScreenMID->SetScalarParameterValue(FName(TEXT("OpacityPercentage")), Time);
		}

		if(bIsLevelLoaded)
		{
			Opacity -= InDeltaTime;
			if(Opacity < 0.0f)
			{
				Opacity = 0.0f;
			}

			EmptyScreenMID->SetScalarParameterValue(FName(TEXT("OpacityPercentage")), Opacity);

			if(Opacity == 0.0f)
			{
				GetMoviePlayer()->StopMovie();
				GetMoviePlayer()->ForceCompletion();
			}
		}
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
