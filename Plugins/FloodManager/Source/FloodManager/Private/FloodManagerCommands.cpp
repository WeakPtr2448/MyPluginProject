// Copyright Epic Games, Inc. All Rights Reserved.

#include "FloodManagerCommands.h"

#define LOCTEXT_NAMESPACE "FFloodManagerModule"

void FFloodManagerCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "FloodManager", "Bring up FloodManager window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
