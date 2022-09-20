// Fill out your copyright notice in the Description page of Project Settings.


#include "SButtonBase.h"

#include "FCommonType.h"
#include "FDataTableTool.h"
#include "Engine/Font.h"

SButtonBase::SButtonBase()
{
}

SButtonBase::~SButtonBase()
{
}

void SButtonBase::Construct(const FArguments& InArgs)
{
	// return;
	FButtonAttr* ButtonAttr = FDTTool::GetButtonAttr(InArgs._Tag);
	UObject* FontLoaded = LoadObject<UFont>(NULL, TEXT("Font'/Engine/EngineFonts/Roboto.Roboto'"));
	UFont* LoadFont = Cast<UFont>(FontLoaded);
	//
	ChildSlot
	[
		SAssignNew(RootSizeBox, SBox)
		[
			SNew(SButton).OnClicked_Lambda([this,InArgs]()
			{
				checkf(InArgs._OnButtonPressed.IsBound(),TEXT("未绑定"));
				InArgs._OnButtonPressed.Execute();
				return FReply::Handled();
			}).HAlign(HAlign_Center).VAlign(VAlign_Center)
			[
				SAssignNew(ButtonText, STextBlock)
				.Font(FSlateFontInfo(LoadFont, ButtonAttr->FontSize))
			]
		]
	];
	// OnButtonClicked = InArgs._OnButtonPressed;
	RootSizeBox->SetWidthOverride(ButtonAttr->ButtonSize.X);
	RootSizeBox->SetHeightOverride(ButtonAttr->ButtonSize.Y);
	RootSizeBox->SetPadding(FMargin(7.f));
	UE_LOG(LogTemp, Warning, TEXT(__FUNCTION__));

	SetButtonText(ButtonAttr->ButtonText);
}

void SButtonBase::SetButtonText(const FString& InText)
{
	this->ButtonText->SetText(FText::FromString(InText));
}

TSharedRef<SButtonBase> SButtonBase::New()
{
	UE_LOG(LogTemp, Warning, TEXT(__FUNCTION__));
	return MakeShareable(new SButtonBase());
}
