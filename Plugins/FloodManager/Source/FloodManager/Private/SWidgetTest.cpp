// Fill out your copyright notice in the Description page of Project Settings.


#include "SWidgetTest.h"

#include "Widgets/Input/SSlider.h"
#include "Widgets/Layout/SGridPanel.h"

SWidgetTest::SWidgetTest()
{
}

SWidgetTest::~SWidgetTest()
{
}

void SWidgetTest::Construct(const FArguments& InArgs)
{
	CheckBoxes.SetNum(2);
	if (Options.Num() <= 0)
	{
		Options.Add(MakeShareable(new FString(TEXT("WTF"))));
		Options.Add(MakeShareable(new FString(TEXT("你干嘛"))));
		Options.Add(MakeShareable(new FString(TEXT("基尼太没"))));
	}

	SUserWidget::Construct(SUserWidget::FArguments().HAlign(HAlign_Fill).VAlign(VAlign_Fill)
	[
		SNew(SGridPanel)
		.FillColumn(0, 0.2f).FillColumn(1, 1.0f)
		.FillRow(0, 1).FillRow(1, 1).FillRow(2, 1.f)
		+ SGridPanel::Slot(0, 0).HAlign(HAlign_Center).VAlign(VAlign_Center)
		[
			SNew(STextBlock).Text(FText::FromString(TEXT("百分比")))
		]
		+ SGridPanel::Slot(0, 1).HAlign(HAlign_Center).VAlign(VAlign_Center)
		[
			SNew(STextBlock).Text(FText::FromString(TEXT("二选一")))
		]
		+ SGridPanel::Slot(0, 2).HAlign(HAlign_Center).VAlign(VAlign_Center)
		[
			SNew(STextBlock).Text(FText::FromString(TEXT("选项")))
		]
		+ SGridPanel::Slot(1, 0).HAlign(HAlign_Fill).VAlign(VAlign_Fill)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot().FillWidth(1.0f)
			[
				SAssignNew(Slider, SSlider) //既可以返回一个共享引用,也可以给一个共享指针赋值
			]
			+ SHorizontalBox::Slot().AutoWidth()
			[
				SNew(STextBlock).Text_Lambda([this]()
				{
					float Value = Slider->GetValue();
					return FText::FromString(FString::SanitizeFloat(Slider.IsValid() ? Value : 0));
				})
			]
		]
		+ SGridPanel::Slot(1, 1).HAlign(HAlign_Fill).VAlign(VAlign_Fill)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			[
				SAssignNew(CheckBoxes[0], SCheckBox)
				.IsChecked(ECheckBoxState::Checked)
				.OnCheckStateChanged_Lambda([this](ECheckBoxState NewState)
				{
					switch (NewState)
					{
					case ECheckBoxState::Checked:
						for (int i = 0; i < CheckBoxes.Num(); ++i)
						{
							if (i != 0 && CheckBoxes[i].IsValid())
							{
								CheckBoxes[i]->SetIsChecked(ECheckBoxState::Unchecked);
							}
						}
						break;
					case ECheckBoxState::Unchecked:
						CheckBoxes[0]->SetIsChecked(ECheckBoxState::Checked);
						break;
					case ECheckBoxState::Undetermined: break;
					default: break;
					}
				})
				[
					SNew(STextBlock).Text(FText::FromString(TEXT("选项一")))
				]

			]
			+ SHorizontalBox::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Fill)
			[
				SAssignNew(CheckBoxes[1], SCheckBox)
			.IsChecked(ECheckBoxState::Unchecked)
			.OnCheckStateChanged_Lambda([this](ECheckBoxState NewState)
				                                    {
					                                    switch (NewState)
					                                    {
					                                    case ECheckBoxState::Checked:
						                                    for (int i = 0; i < CheckBoxes.Num(); ++i)
						                                    {
							                                    if (i != 1 && CheckBoxes[i].IsValid())
							                                    {
								                                    CheckBoxes[i]->SetIsChecked(
									                                    ECheckBoxState::Unchecked);
							                                    }
						                                    }
						                                    break;
					                                    case ECheckBoxState::Unchecked:
						                                    CheckBoxes[1]->SetIsChecked(ECheckBoxState::Checked);
						                                    break;
					                                    case ECheckBoxState::Undetermined: break;
					                                    default: break;
					                                    }
				                                    })
				[
					SNew(STextBlock).Text(FText::FromString(TEXT("选项二")))
				]
			]
		]
		+ SGridPanel::Slot(1, 2).HAlign(HAlign_Fill).VAlign(VAlign_Fill)
		[
			SNew(SComboBox<TSharedPtr<FString>>)
			.OnGenerateWidget_Lambda([](TSharedPtr<FString> Item)
			                                    {
				                                    return SNew(STextBlock).Text(FText::FromString(*Item));
			                                    })
			.OnSelectionChanged_Lambda([this](TSharedPtr<FString> Item,
			                                  ESelectInfo::Type Type)
			                                    {
				                                    if (ComboText.IsValid())
				                                    {
					                                    ComboText->SetText(FText::FromString(*Item));
				                                    }
			                                    })

			[
				SAssignNew(ComboText, STextBlock)
			]
			.OptionsSource(&Options)
		]
	]);
	//
}

TSharedRef<SWidgetTest> SWidgetTest::New()
{
	return MakeShareable(new SWidgetTest());
}
