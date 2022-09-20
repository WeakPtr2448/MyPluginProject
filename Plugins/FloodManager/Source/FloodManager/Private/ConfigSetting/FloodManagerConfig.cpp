// Fill out your copyright notice in the Description page of Project Settings.

#include "ConfigSetting/FloodManagerConfig.h"

UFloodManagerConfig::UFloodManagerConfig(const FObjectInitializer& Initializer): Super(Initializer)
{
	FunctionTitle.Add(FString("ImportFileAction"));
	FunctionTitle.Add(FString("Settings"));
	FunctionTitle.Add(FString("WaterSettings"));

	ButtonRowNames.Add(FString("ImportButton"));
	ButtonRowNames.Add(FString("StartGame"));
	ButtonRowNames.Add(FString("ColorButton"));

	GConfig->SetArray(TEXT("/Script/FloodManager.FloodManagerConfig"),TEXT("ButtonRowNames"), ButtonRowNames, GGameIni);
	GConfig->SetArray(TEXT("/Script/FloodManager.FloodManagerConfig"),TEXT("FunctionTitle"), FunctionTitle, GGameIni);
}


// bool UFloodManagerConfig::WriteIni(FString NewKey, FString NewValue)
// {
// 	if (!GConfig)
// 		return false;
// 	GConfig->SetString(TEXT("Flood"), *NewKey, *NewValue, GGameIni);
//
// 	return true;
// }
