#include "Setting/UnrealCSharpEditorSetting.h"
#if WITH_EDITOR
#include "ISettingsModule.h"
#endif
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "UEVersion.h"
#if WITH_EDITOR
#include "CoreMacro/Macro.h"
#include "Engine/Blueprint.h"
#include "WidgetBlueprint.h"
#include "Engine/UserDefinedEnum.h"
#include "Engine/UserDefinedStruct.h"
#endif

#define LOCTEXT_NAMESPACE "FUnrealCSharpEditorSettings"

UUnrealCSharpEditorSetting::UUnrealCSharpEditorSetting(const FObjectInitializer& ObjectInitializer):
#if WITH_EDITOR
	Super(ObjectInitializer),
	ScriptDirectory(DEFAULT_SCRIPT_DIRECTORY),
	bEnableCompiled(true),
	bEnableAssetChanged(true),
	bEnableDirectoryChanged(true),
	bIsSkipGenerateEngineModules(false),
	bIsGenerateAllModules(true),
	bIsGenerateAsset(true),
	bIsGenerateFunctionComment(true),
	bEnableExport(false)
#else
	Super(ObjectInitializer)
#endif
{
}

#if WITH_EDITOR
void UUnrealCSharpEditorSetting::RegisterSettings()
{
	if (const auto SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		static TSet<FString> DefaultSupportedModules =
		{
			TEXT("Core"),
			TEXT("CoreUObject"),
			TEXT("Engine"),
			TEXT("SlateCore"),
#if UE_FIELD_NOTIFICATION
			TEXT("FieldNotification"),
#endif
			TEXT("UMG"),
			TEXT("UnrealCSharpCore"),
			FApp::GetProjectName()
		};

		static TSet<FString> DefaultSupportedAssetPaths =
		{
			FApp::GetProjectName()
		};

		static TSet<TSubclassOf<UObject>> DefaultSupportedAssetClasses =
		{
			UBlueprint::StaticClass(),
			UUserDefinedStruct::StaticClass(),
			UUserDefinedEnum::StaticClass(),
			UWidgetBlueprint::StaticClass()
		};

		const auto MutableDefaultUnrealCSharpEditorSetting = GetMutableDefault<UUnrealCSharpEditorSetting>();

		for (const auto& DefaultSupportedModule : DefaultSupportedModules)
		{
			MutableDefaultUnrealCSharpEditorSetting->SupportedModule.AddUnique(DefaultSupportedModule);
		}

		for (const auto& DefaultSupportedAssetPath : DefaultSupportedAssetPaths)
		{
			MutableDefaultUnrealCSharpEditorSetting->SupportedAssetPath.AddUnique(DefaultSupportedAssetPath);
		}

		for (const auto& DefaultSupportedAssetClass : DefaultSupportedAssetClasses)
		{
			MutableDefaultUnrealCSharpEditorSetting->SupportedAssetClass.AddUnique(DefaultSupportedAssetClass);
		}

		SettingsModule->RegisterSettings("Editor",
		                                 "Plugins",
		                                 "UnrealCSharpEditorSettings",
		                                 LOCTEXT("UnrealCSharpEditorSettingsName",
		                                         "UnrealCSharp Editor Setting"),
		                                 LOCTEXT("UnrealCSharpEditorSettingsDescription",
		                                         "UnrealCSharp Editor Setting"),
		                                 MutableDefaultUnrealCSharpEditorSetting);
	}
}

void UUnrealCSharpEditorSetting::UnregisterSettings()
{
	if (const auto SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Editor",
		                                   "Plugins",
		                                   "UnrealCSharpEditorSettings");
	}
}

const FString& UUnrealCSharpEditorSetting::GetDotNetPath() const
{
	return DotNetPath;
}

TArray<FString> UUnrealCSharpEditorSetting::GetDotNetPathArray() const
{
#if PLATFORM_WINDOWS
	// https://learn.microsoft.com/en-us/dotnet/core/install/how-to-detect-installed-versions?pivots=os-windows
	const FString DotNet = TEXT("dotnet");

	const FString Params = TEXT("--list-sdks");

	void* ReadPipe = nullptr;

	void* WritePipe = nullptr;

	auto OutProcessID = 0u;

	FString Result;

	FPlatformProcess::CreatePipe(ReadPipe, WritePipe);

	auto ProcessHandle = FPlatformProcess::CreateProc(
		*DotNet,
		*Params,
		false,
		true,
		true,
		&OutProcessID,
		1,
		nullptr,
		WritePipe,
		ReadPipe);

	while (ProcessHandle.IsValid() && FPlatformProcess::IsApplicationRunning(OutProcessID))
	{
		FPlatformProcess::Sleep(0.01f);

		Result.Append(FPlatformProcess::ReadPipe(ReadPipe));
	}

	auto ReturnCode = 0;

	if (FPlatformProcess::GetProcReturnCode(ProcessHandle, &ReturnCode))
	{
		if (ReturnCode == 0)
		{
			// @TODO
		}
		else
		{
			// @TODO
		}
	}

	TArray<FString> ResultArray;

	FString Left;

	FString Right;

	while (Result.Split(TEXT("\r\n"), &Left, &Right))
	{
		// 需要匹配 3.1.424 [C:\program files\dotnet\sdk]  这样的字符串
		// 这里简单检测一下,
		// 1. 提取第一个空格前的字符串,通过 . 来分割,如果分割后的数组长度大于等于3并且是数字,则认为是正确版本号 否则直接返回默认路径
		{
			auto SpaceIndex = 0;

			if (!Left.FindChar(' ', SpaceIndex))
			{
				// 没有找到空格,直接返回默认路径
				break;
			}

			auto VersionString = Left.Left(SpaceIndex);

			TArray<FString> VersionArray;

			VersionString.ParseIntoArray(VersionArray,TEXT("."));

			if (VersionArray.Num() >= 3)
			{
				auto bIsVersion = true;

				for (const auto& Version : VersionArray)
				{
					if (!Version.IsNumeric())
					{
						bIsVersion = false;

						break;
					}
				}
				if (bIsVersion)
				{
					auto PathString = Left.Right(Left.Len() - SpaceIndex);

					PathString = PathString.TrimStartAndEnd();

					// 去除前后括号[] 把 \ 转换成 / 并且去除最后的 sdk 路径 加上 dotnet.exe
					PathString = PathString[0] == '[' ? PathString.Right(PathString.Len() - 1) : PathString;

					PathString = PathString[PathString.Len() - 1] == ']'
						             ? PathString.Left(PathString.Len() - 1)
						             : PathString;

					PathString = PathString.Replace(TEXT("\\"),TEXT("/"));

					PathString = PathString.EndsWith(TEXT("sdk"))
						             ? PathString.Left(PathString.Len() - 3)
						             : PathString;

					PathString = PathString + TEXT("dotnet.exe");

					// 路径唯一,添加到数组
					ResultArray.AddUnique(PathString);
				}
				else
				{
					// 不是版本号,直接返回默认路径
					break;
				}
			}
		}

		Result = Right;
	}

	if (ResultArray.IsEmpty())
	{
		ResultArray.Add(TEXT(""));
	}

	FPlatformProcess::ClosePipe(ReadPipe, WritePipe);

	FPlatformProcess::CloseProc(ProcessHandle);

	// 运行失败,返回默认路径
	return ResultArray;
#elif PLATFORM_MAC
	return {TEXT("/usr/local/share/dotnet/dotnet")};
#endif
}

const FProjectDirectoryPath& UUnrealCSharpEditorSetting::GetScriptDirectory() const
{
	return ScriptDirectory;
}

bool UUnrealCSharpEditorSetting::EnableCompiled() const
{
	return bEnableCompiled;
}

bool UUnrealCSharpEditorSetting::EnableAssetChanged() const
{
	return bEnableAssetChanged;
}

bool UUnrealCSharpEditorSetting::EnableDirectoryChanged() const
{
	return bEnableDirectoryChanged;
}

bool UUnrealCSharpEditorSetting::IsSkipGenerateEngineModules() const
{
	return bIsSkipGenerateEngineModules;
}

bool UUnrealCSharpEditorSetting::IsGenerateAllModules() const
{
	return bIsGenerateAllModules;
}

const TArray<FString>& UUnrealCSharpEditorSetting::GetSupportedModule() const
{
	return SupportedModule;
}

bool UUnrealCSharpEditorSetting::IsGenerateAsset() const
{
	return bIsGenerateAsset;
}

const TArray<FString>& UUnrealCSharpEditorSetting::GetSupportedAssetPath() const
{
	return SupportedAssetPath;
}

const TArray<TSubclassOf<UObject>>& UUnrealCSharpEditorSetting::GetSupportedAssetClass() const
{
	return SupportedAssetClass;
}

bool UUnrealCSharpEditorSetting::IsGenerateFunctionComment() const
{
	return bIsGenerateFunctionComment;
}

TArray<FString> UUnrealCSharpEditorSetting::GetModuleList()
{
	TArray<FString> ModuleArray;

	const auto& ProjectModules = FUnrealCSharpFunctionLibrary::GetProjectModuleList();

	const auto& EngineModules = FUnrealCSharpFunctionLibrary::GetEngineModuleList();

	for (const auto& ProjectModule : ProjectModules)
	{
		ModuleArray.AddUnique(ProjectModule);
	}

	for (const auto& EngineModule : EngineModules)
	{
		ModuleArray.AddUnique(EngineModule);
	}

	return ModuleArray;
}
#endif

#undef LOCTEXT_NAMESPACE
