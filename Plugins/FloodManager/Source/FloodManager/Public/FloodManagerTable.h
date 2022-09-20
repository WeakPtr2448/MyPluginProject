// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SUserWidget.h"

/**
 * 
 */
class FloodManagerTable : public SUserWidget
{
public:
	FloodManagerTable();
	~FloodManagerTable();

public:
	SLATE_USER_ARGS(FloodManagerTable)
		{
		}

	SLATE_END_ARGS()

	// MUST Provide this function for SNew to call!
	virtual void Construct(const FArguments& InArgs);

private:
	TSharedPtr<SEditableTextBox> EditableTextBox;

	TSharedPtr<class SButtonBase> ImportButton;
	TSharedPtr<class SButtonBase> StartButton;
	TSharedPtr<class SButtonBase> ColorButton;

	TSharedPtr<class SSlider> Slider;
	TSharedPtr<class SCheckBox> CheckBox;
	TSharedPtr<class SColorPicker> ColorPicker;
	TSharedPtr<class STextBlock> ComboString;

	FLinearColor CurrentColor;
};
