// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FloodManagerConfig.generated.h"

/**
 * 
 */
UCLASS(Config=Game)
class FLOODMANAGER_API UFloodManagerConfig : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	UPROPERTY(EditAnywhere, Config, Category="MainMenu")
	TArray<FString> FunctionTitle;

	UPROPERTY(EditAnywhere,Config,Category="MainMenu")
	TArray<FString> ButtonRowNames;
	//
	// UPROPERTY(EditAnywhere,Config,Category="MainMenu")
	// FString Title_3 = FString("WaterSettings");

private:
	//写入配置文件
	//bool WriteIni(FString NewKey,FString NewValue);
};
