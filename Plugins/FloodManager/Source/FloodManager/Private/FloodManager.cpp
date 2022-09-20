// Copyright Epic Games, Inc. All Rights Reserved.

#include "FloodManager.h"
#include "FloodManagerStyle.h"
#include "ISettingsModule.h"
#include "FloodManagerCommands.h"
#include "LevelEditor.h"
#include"FloodManagerTable.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "ConfigSetting/FloodManagerConfig.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "Widgets/Input/SSlider.h"

static const FName FloodManagerTableName("FloodManagerTableName");

#define LOCTEXT_NAMESPACE "FFloodManagerModule"
#define LOCTEXT_1 "FloodManager"
#define LOCTEXT_2 "FloodManagerConfigDiscription"

void FFloodManagerModule::RegisterConfig()
{
	//注册配置到项目设置中
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings(
			"Project",
			"Plugins",
			"Flood",
			LOCTEXT("FloodManager", "FloodManager"),
			LOCTEXT("FloodManagerConfigDiscription", "FloodManagerConfigDiscription"),
			GetMutableDefault<UFloodManagerConfig>()
		);
	}
}

void FFloodManagerModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	//
	RegisterConfig();

	FFloodManagerStyle::Initialize();
	FFloodManagerStyle::ReloadTextures();

	FFloodManagerCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FFloodManagerCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FFloodManagerModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(
		FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FFloodManagerModule::RegisterMenus));
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(FloodManagerTableName,
	                                                  FOnSpawnTab::CreateLambda([](const FSpawnTabArgs& SpawnTabArgs)
	                                                  {
		                                                  return SNew(SDockTab).TabRole(ETabRole::NomadTab)
		                                                  [
			                                                  SNew(FloodManagerTable)
		                                                  ];
	                                                  }))
	                        .SetDisplayName(LOCTEXT("FFloodManagerTabTitle", "宏安四维洪水推演工具"))
	                        .SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FFloodManagerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	//
	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FFloodManagerStyle::Shutdown();

	FFloodManagerCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterTabSpawner(FloodManagerTableName);
}

TSharedRef<SDockTab> FFloodManagerModule::OnSpawnFloodTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText ButtonText = LOCTEXT("WindowWidgetText", "这是我的按钮");

	return SNew(SDockTab)
		.TabRole(NomadTab)[
			SNew(SBox)
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
			[
				SNew(SButton)
			.Text(ButtonText)
			.OnPressed_Lambda([]()
				             {
					             GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green,TEXT(__FUNCTION__));
				             })
			]

		];
}

TSharedRef<SDockTab> FFloodManagerModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FFloodManagerModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("FloodManager.cpp"))
	);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FFloodManagerModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(FloodManagerTableName);
}

void FFloodManagerModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FFloodManagerCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(
					FToolMenuEntry::InitToolBarButton(FFloodManagerCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}


#undef LOCTEXT_NAMESPACE
#undef LOCTEXT_1
#undef LOCTEXT_2

IMPLEMENT_MODULE(FFloodManagerModule, FloodManager)
