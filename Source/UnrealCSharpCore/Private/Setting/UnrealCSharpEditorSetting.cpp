#include "Setting/UnrealCSharpEditorSetting.h"
#if WITH_EDITOR
#include "ISettingsModule.h"
#endif
#include "UEVersion.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"

#define LOCTEXT_NAMESPACE "FUnrealCSharpEditorSettings"

#if WITH_EDITOR
void UUnrealCSharpEditorSetting::RegisterSettings()
{
	if (const auto SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Editor",
		                                 "Plugins",
		                                 "UnrealCSharpEditorSettings",
		                                 LOCTEXT("UnrealCSharpEditorSettingsName",
		                                         "UnrealCSharp Editor Setting"),
		                                 LOCTEXT("UnrealCSharpEditorSettingsDescription",
		                                         "UnrealCSharp Editor Setting"),
		                                 GetMutableDefault<UUnrealCSharpEditorSetting>());
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

#if PLATFORM_WINDOWS
					PathString = PathString + TEXT("dotnet.exe");
#else
					PathStr = PathStr + TEXT("dotnet");
#endif

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

#if UE_ARRAY_IS_EMPTY
	if (ResultArray.IsEmpty())
#else
	if (ResultArray.Num() <= 0)
#endif
	{
		ResultArray.Add(TEXT(""));
	}

	FPlatformProcess::ClosePipe(ReadPipe, WritePipe);

	FPlatformProcess::CloseProc(ProcessHandle);

	// 运行失败,返回默认路径
	return ResultArray;
}

const TArray<FString>& UUnrealCSharpEditorSetting::GetSupportedModule()
{
	return SupportedModule;
}

const TArray<FString>& UUnrealCSharpEditorSetting::GetSupportedAssetPath()
{
	return SupportedAssetPath;
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

	ModuleArray.Remove(TEXT("Game"));

	return ModuleArray;
}
#endif

#undef LOCTEXT_NAMESPACE
