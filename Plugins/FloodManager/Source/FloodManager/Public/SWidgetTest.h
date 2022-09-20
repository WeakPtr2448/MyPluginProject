// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SUserWidget.h"

/**
 * 
 */
class  SWidgetTest:public SUserWidget
{
public:
	SWidgetTest();
	~SWidgetTest();
public:
	SLATE_USER_ARGS(SWidgetTest)
	{
	}

	SLATE_END_ARGS()

	// MUST Provide this function for SNew to call!
	virtual void Construct(const FArguments& InArgs);


private:
	TSharedPtr<class SSlider> Slider;
	TArray<TSharedPtr<SCheckBox>> CheckBoxes;
	TSharedPtr<STextBlock> ComboText;

	TArray<TSharedPtr<FString>> Options;
};
