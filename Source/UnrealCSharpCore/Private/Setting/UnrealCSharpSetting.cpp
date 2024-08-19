#include "Setting/UnrealCSharpSetting.h"
#include "CoreMacro/Macro.h"
#if WITH_EDITOR
#include "ISettingsModule.h"
#endif

#define LOCTEXT_NAMESPACE "FUnrealCSharpSettings"

UUnrealCSharpSetting::UUnrealCSharpSetting(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	  PublishDirectory(DEFAULT_PUBLISH_DIRECTORY),
	  UEName(DEFAULT_UE_NAME),
	  GameName(DEFAULT_GAME_NAME),
	  AssemblyLoader(UAssemblyLoader::StaticClass()),
	  bEnableDebug(false),
	  Port(0)
{
}

#if WITH_EDITOR
void UUnrealCSharpSetting::RegisterSettings()
{
	if (const auto SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Project",
		                                 "Plugins",
		                                 "UnrealCSharpSettings",
		                                 LOCTEXT("UnrealCSharpSettingsName",
		                                         "UnrealCSharp Setting"),
		                                 LOCTEXT("UnrealCSharpSettingsDescription",
		                                         "UnrealCSharp Setting"),
		                                 GetMutableDefault<UUnrealCSharpSetting>());
	}
}

void UUnrealCSharpSetting::UnregisterSettings()
{
	if (const auto SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project",
		                                   "Plugins",
		                                   "UnrealCSharpSettings");
	}
}
#endif

const FGameContentDirectoryPath& UUnrealCSharpSetting::GetPublishDirectory() const
{
	return PublishDirectory;
}

const FString& UUnrealCSharpSetting::GetUEName() const
{
	return UEName;
}

const FString& UUnrealCSharpSetting::GetGameName() const
{
	return GameName;
}

UAssemblyLoader* UUnrealCSharpSetting::GetAssemblyLoader() const
{
	return Cast<UAssemblyLoader>((AssemblyLoader->IsValidLowLevelFast()
		                              ? AssemblyLoader.Get()
		                              : UAssemblyLoader::StaticClass())
		->GetDefaultObject());
}

const TArray<FBindClass>& UUnrealCSharpSetting::GetBindClass() const
{
	return BindClass;
}

bool UUnrealCSharpSetting::IsEnableDebug() const
{
	return bEnableDebug;
}

const FString& UUnrealCSharpSetting::GetHost() const
{
	return Host;
}

int32 UUnrealCSharpSetting::GetPort() const
{
	return Port;
}

#undef LOCTEXT_NAMESPACE
