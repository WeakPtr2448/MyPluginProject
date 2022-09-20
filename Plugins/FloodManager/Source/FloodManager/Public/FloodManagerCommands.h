// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "FloodManagerStyle.h"

class FFloodManagerCommands : public TCommands<FFloodManagerCommands>
{
public:

	FFloodManagerCommands()
		: TCommands<FFloodManagerCommands>(TEXT("FloodManager"), NSLOCTEXT("Contexts", "FloodManager", "FloodManager Plugin"), NAME_None, FFloodManagerStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};