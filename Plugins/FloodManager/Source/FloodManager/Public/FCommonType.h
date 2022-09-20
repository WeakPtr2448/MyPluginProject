// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FCommonType.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FFloodManagerAttr : public FTableRowBase
{
	GENERATED_BODY()

	//内容文本
	UPROPERTY(EditAnywhere, Category="General")
	FText TitleText;

	//子控件大小
	UPROPERTY(EditAnywhere, Category="General")
	FVector2D ChildPanelSize;

	//内容文本
	UPROPERTY(EditAnywhere, Category="Content")
	TArray<FText> ContentText;

	//内容文本字体大小
	UPROPERTY(EditAnywhere,Category="Content")
	int32 ContentTextFontSize;

	//字体路径
	UPROPERTY(EditAnywhere, Category="FontSetting")
	FString FontPath;

	//主UI字体大小
	UPROPERTY(EditAnywhere, Category="FontSetting")
	int32 MainFontSize;
};

USTRUCT(BlueprintType, Blueprintable)
struct FButtonAttr : public FTableRowBase
{
	GENERATED_BODY()

	//按钮大小
	UPROPERTY(EditAnywhere, Category="General")
	FVector2D ButtonSize;

	//字体路径
	UPROPERTY(EditAnywhere, Category="FontSetting")
	FString FontPath;

	//主UI字体大小
	UPROPERTY(EditAnywhere, Category="FontSetting")
	int32 FontSize;

	//按钮文字
	UPROPERTY(EditAnywhere, Category="FontSetting")
	FString ButtonText;
};

/**
 * 
 */
UCLASS()
class FLOODMANAGER_API UFCommonType : public UObject
{
	GENERATED_BODY()
};
