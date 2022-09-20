// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FCommonType.h"
#include "Widgets/SUserWidget.h"

DECLARE_MULTICAST_DELEGATE(FOnButtonClicked);


/**
 * 
 */
class SButtonBase : public SUserWidget
{
public:
	SButtonBase();
	~SButtonBase();

	SLATE_USER_ARGS(SButtonBase)
		{
		}

	SLATE_END_ARGS()
	
	
	FOnButtonClicked OnButtonClicked;

	// MUST Provide this function for SNew to call!
	virtual void Construct(const FArguments& InArgs);


private:
	void SetButtonText(const FString& InText);
	
	TSharedPtr<SBox> RootSizeBox;
	
	TSharedPtr<STextBlock> ButtonText;
};
