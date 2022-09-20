// Fill out your copyright notice in the Description page of Project Settings.


#include "FloodManagerTable.h"

#include "FDataTableTool.h"
#include "SButtonBase.h"
#include "AppFramework/Public/Widgets/Colors/SColorPicker.h"
#include "Engine/Font.h"
#include "Slate/Private/Widgets/Views/SListPanel.h"
#include "Widgets/Colors/SColorBlock.h"
#include "Widgets/Input/SSlider.h"
#include "Widgets/Layout/SGridPanel.h"
#include "Widgets/Layout/SScrollBox.h"

#define FONT_PATH "Font'/Engine/EngineFonts/Roboto.Roboto'"

FloodManagerTable::FloodManagerTable()
{
}

FloodManagerTable::~FloodManagerTable()
{
}

TSharedRef<FloodManagerTable> FloodManagerTable::New()
{
	return MakeShareable(new FloodManagerTable());
}

void FloodManagerTable::Construct(const FArguments& InArgs)
{
	// return;
	TArray<FString> NameArr;
	TArray<FFloodManagerAttr*> ManagerAttrs;
	GConfig->GetArray(TEXT("/Script/FloodManager.FloodManagerConfig"),TEXT("FunctionTitle"), NameArr, GGameIni);
	for (FString Arr : NameArr)
	{
		FFloodManagerAttr* FloodManagerAttr = FDTTool::GetFloodManagerAttr(FName(*Arr));
		ManagerAttrs.Add(FloodManagerAttr);
	}

	TArray<FString> ButtonNameArr;
	GConfig->GetArray(TEXT("/Script/FloodManager.FloodManagerConfig"),TEXT("ButtonRowNames"), ButtonNameArr, GGameIni);

	UE_LOG(LogTemp, Warning, TEXT("长度为%s"), *ManagerAttrs[0]->TitleText.ToString());

	if (ManagerAttrs.Num() < 0)return;

	UObject* FontLoaded = LoadObject<UFont>(NULL,TEXT(FONT_PATH));
	UFont* loadFont = Cast<UFont>(FontLoaded);

	SUserWidget::Construct(SUserWidget::FArguments()
		.HAlign(HAlign_Fill)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.FillHeight(1.0f)
			[
				SNew(SGridPanel)
				.FillColumn(0, 1).FillColumn(1, 3)
				.FillRow(0, 1).FillRow(1, 1).FillRow(2, 1)
				+ SGridPanel::Slot(0, 0)
				  .HAlign(HAlign_Center)
				  .VAlign(VAlign_Center)
				[
					SNew(STextBlock).Text(ManagerAttrs[0]->TitleText)
					                .Font(FSlateFontInfo(loadFont, ManagerAttrs[0]->MainFontSize))
				]
				+ SGridPanel::Slot(1, 0)
				[
					SNew(SBorder)
					.BorderBackgroundColor(FLinearColor(FVector4(0.12f, 0.12f, 0.12f, 0.6f)))
					.Padding(FMargin(6.f))
					[
						SNew(SHorizontalBox)
						+ SHorizontalBox::Slot()
						  .HAlign(HAlign_Left)
						  .VAlign(VAlign_Center)
						  .FillWidth(1)
						[
							SNew(SBox)
										.WidthOverride(ManagerAttrs[0]->ChildPanelSize.X)
										.HeightOverride(ManagerAttrs[0]->ChildPanelSize.Y)
							[
								SAssignNew(EditableTextBox, SEditableTextBox)
							]
						]
						+ SHorizontalBox::Slot()
						  .HAlign(HAlign_Left)
						  .VAlign(VAlign_Center)
						  .FillWidth(0.5)
						[
							SAssignNew(ImportButton, SButtonBase)
							.Tag(*ButtonNameArr[0])
							.OnButtonPressed_Lambda([]()
							{
								//TODO
								UE_LOG(LogTemp, Log, TEXT("导入ShapeFile文件"));
								GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,TEXT("导入ShapeFile文件"));
							})
						]
					]

				]
				+ SGridPanel::Slot(0, 1)
				  .HAlign(HAlign_Center)
				  .VAlign(VAlign_Center)
				[
					SNew(STextBlock).Text(ManagerAttrs[1]->TitleText)
					                .Font(FSlateFontInfo(loadFont, ManagerAttrs[1]->MainFontSize))
				]
				+ SGridPanel::Slot(0, 2)
				  .HAlign(HAlign_Center)
				  .VAlign(VAlign_Center)
				[
					SNew(STextBlock).Text(ManagerAttrs[2]->TitleText)
					                .Font(FSlateFontInfo(loadFont, ManagerAttrs[2]->MainFontSize))
				]
				+ SGridPanel::Slot(1, 1)
				[
					SNew(SBorder)
				.BorderBackgroundColor(FLinearColor(FVector4(0.12f, 0.12f, 0.12f, 0.6f)))
				.Padding(FMargin(6.f))
					[
						SNew(SGridPanel)
						.FillColumn(0, 1).FillColumn(1, 3)
						.FillRow(0, 1).FillRow(1, 1)
						+ SGridPanel::Slot(0, 0)
						  .HAlign(HAlign_Left).Padding(10, 0, 0, 0)
						  .VAlign(VAlign_Center)
						[
							SNew(STextBlock)
							.Text(ManagerAttrs[1]->ContentText[0])
							.Font(FSlateFontInfo(loadFont, ManagerAttrs[1]->ContentTextFontSize))
						]
						+ SGridPanel::Slot(0, 1)
						  .HAlign(HAlign_Left).Padding(10, 0, 0, 0)
						  .VAlign(VAlign_Center)
						[
							SNew(STextBlock)
							.Text(ManagerAttrs[1]->ContentText[1])
							.Font(FSlateFontInfo(loadFont, ManagerAttrs[1]->ContentTextFontSize))
						]
						+ SGridPanel::Slot(1, 0)
						  .Padding(FMargin(15.f, 0, 15, 0))
						  .VAlign(VAlign_Center)
						[
							SAssignNew(Slider, SSlider)
							.MinValue(0)
							.MaxValue(3)
							.OnValueChanged_Lambda([](float InValue)
							{
								//TODO...
							})
						]
						+ SGridPanel::Slot(1, 1)
						[
							SAssignNew(CheckBox, SCheckBox)
							.OnCheckStateChanged_Lambda([](ECheckBoxState CheckState)
							{
								//TODO...
							})
						]
					]
				]
				+ SGridPanel::Slot(1, 2)
				[
					SNew(SBorder)
					.BorderBackgroundColor(FLinearColor(FVector4(0.12f, 0.12f, 0.12f, 0.6f)))
					.Padding(FMargin(6.f))
					[
						SNew(SScrollBox)
						+ SScrollBox::Slot()
						[
							SNew(SBorder)
							.BorderBackgroundColor(FSlateColor(FLinearColor(FVector4(0, 0, 0, 0.8f))))
							[
								SNew(SSplitter)
								+ SSplitter::Slot()
								[
									SNew(STextBlock)
									.Margin(FMargin(6.f, 0, 0, 0))
									.Font(FSlateFontInfo(loadFont, ManagerAttrs[2]->ContentTextFontSize))
									.Text(ManagerAttrs[2]->ContentText[0])
								]
								+ SSplitter::Slot()
								[
									SNew(SColorBlock)
									.Color(FLinearColor(FVector4(1, 1, 1, 1)))
									.Color_Lambda([this]()-> FLinearColor
									                 {
										                 return CurrentColor;
									                 })
									                 .OnMouseButtonDown_Lambda(
										                 [this](const FGeometry& Geometry,
										                        const FPointerEvent& PointerEvent)
										                 {
											                 UE_LOG(LogTemp, Log, TEXT("打开颜色面板"));
											                 GEngine->AddOnScreenDebugMessage(
												                 -1, 5.f, FColor::Green,
												                 TEXT("打开颜色面板"));

											                 SAssignNew(ColorPicker, SColorPicker)
												                 .OnColorCommitted_Lambda(
													                 [this](FLinearColor InColor)
													                 {
														                 CurrentColor = InColor;
														                 UE_LOG(LogTemp, Warning,
															                 TEXT("当前颜色为: %s"),
															                 *InColor.ToString());
													                 });
											                 return FReply::Handled();
										                 })
								]
							]
						]
					]
				]
			]
			+ SVerticalBox::Slot()
			  .AutoHeight()
			  .HAlign(HAlign_Center)
			  .VAlign(VAlign_Center)
			  .Padding(FMargin(0, 0, 0, 8))
			[
				SAssignNew(StartButton, SButtonBase).Tag(*ButtonNameArr[1])
				                                    .OnButtonPressed_Lambda([]()
				                                    {
					                                    GEngine->AddOnScreenDebugMessage(
						                                    -1, 5.f, FColor::Red,TEXT("开始推演"));
					                                    UE_LOG(LogTemp, Log, TEXT("开始推演"));
					                                    //TODO...
				                                    })
			]
		]);
	UE_LOG(LogTemp, Warning, TEXT(__FUNCTION__));
}
