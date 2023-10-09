#include "Setting/UnrealCSharpEditorSetting.h"

#include "ISettingsModule.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Misc/MonitoredProcess.h"

#define LOCTEXT_NAMESPACE "FUnrealCSharpEditorSettings"

TArray<FString> FUnrealCSharpEditorSettingsHelper::LogOutPutMessage = {};

UUnrealCSharpEditorSetting::UUnrealCSharpEditorSetting(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {}

TArray<FString> UUnrealCSharpEditorSetting::GetDotNetPath() const
{
	// https://learn.microsoft.com/en-us/dotnet/core/install/how-to-detect-installed-versions?pivots=os-windows
	const FString RunCommand = TEXT("dotnet");
	const FString Parms      = TEXT("--list-sdks");

	const TSharedPtr<FMonitoredProcess> RunProcess =
		MakeShareable(new FMonitoredProcess(RunCommand, Parms, true));
	FString OutputMessage = TEXT("");

	FUnrealCSharpEditorSettingsHelper::LogOutPutMessage.Empty();
	RunProcess->OnOutput().BindStatic(&FUnrealCSharpEditorSettingsHelper::OnStatusOutput);
	RunProcess->Launch();
	while ( RunProcess->Update() )
	{
		FPlatformProcess::Sleep(0.01f);
	}

	TArray<FString> ResultPathArray;

	if ( FUnrealCSharpEditorSettingsHelper::LogOutPutMessage.Num() > 0 )
	{
		// 需要匹配 3.1.424 [C:\program files\dotnet\sdk]  这样的字符串
		// 这里简单检测一下,
		// 1. 提取第一个空格前的字符串,通过 . 来分割,如果分割后的数组长度大于等于3并且是数字,则认为是正确版本号 否则直接返回默认路径
		for ( auto Command : FUnrealCSharpEditorSettingsHelper::LogOutPutMessage )
		{
			int SpaceIndex        = 0;
			const auto FindResult = Command.FindChar(' ', SpaceIndex);
			if ( !FindResult )
			{
				// 没有找到空格,直接返回默认路径
				break;
			}
			FString VersionStr = Command.Left(SpaceIndex);
			TArray<FString> VersionArray;
			VersionStr.ParseIntoArray(VersionArray,TEXT("."));
			if ( VersionArray.Num() >= 3 )
			{
				bool IsVersion = true;
				for ( auto Version : VersionArray )
				{
					if ( !Version.IsNumeric() )
					{
						IsVersion = false;
						break;
					}
				}
				if ( IsVersion )
				{
					auto PathStr = Command.Right(Command.Len() - SpaceIndex);
					PathStr      = PathStr.TrimStartAndEnd();
					// 去除前后括号[] 把 \ 转换成 / 并且去除最后的 sdk 路径 加上 dotnet.exe
					PathStr = PathStr[0] == '[' ? PathStr.Right(PathStr.Len() - 1) : PathStr;
					PathStr = PathStr[PathStr.Len() - 1] == ']' ? PathStr.Left(PathStr.Len() - 1) : PathStr;
					PathStr = PathStr.Replace(TEXT("\\"),TEXT("/"));
					PathStr = PathStr.EndsWith(TEXT("sdk")) ? PathStr.Left(PathStr.Len() - 3) : PathStr;
#if PLATFORM_WINDOWS
					PathStr = PathStr + TEXT("dotnet.exe");
#else
					PathStr = PathStr + TEXT("dotnet");
#endif

					// 路径唯一,添加到数组
					ResultPathArray.AddUnique(PathStr);
				}
				else
				{
					// 不是版本号,直接返回默认路径
					break;
				}
			}
		}
	}

	if ( ResultPathArray.Num() <= 0 )
	{
		ResultPathArray.Add(TEXT(""));
	}

	// 运行失败,返回默认路径
	return ResultPathArray;
}

TArray<FString> UUnrealCSharpEditorSetting::GenModulesList()
{
	TArray<FString> ModuleListItems;


	TArray<FModuleStatus> ModuleStatuses;
	FModuleManager::Get().QueryModules(ModuleStatuses);

	for ( TArray<FModuleStatus>::TConstIterator ModuleIt(ModuleStatuses) ; ModuleIt ; ++ModuleIt )
	{
		const FModuleStatus& ModuleStatus = *ModuleIt;

		ModuleListItems.AddUnique(ModuleStatus.Name);
	}

	return ModuleListItems;
}

void UUnrealCSharpEditorSetting::PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent)
{
	UObject::PostEditChangeChainProperty(PropertyChangedEvent);
	if ( PropertyChangedEvent.GetPropertyName() == TEXT("DotNetPath") )
	{
		FUnrealCSharpFunctionLibrary::DotNetPath = DotNetPath;
	}
}


#if WITH_EDITOR


void FUnrealCSharpEditorSettingsHelper::RegisterSettings()
{
	// 项目设置
	if ( ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings") )
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "UnrealCSharpEditorSettings",
		                                 LOCTEXT("UnrealCSharpEditorSettingsName", "UnrealCSharp Editor Setting"),
		                                 LOCTEXT("UnrealCSharpEditorSettingsDescription",
		                                         "UnrealCSharp Editor Setting"),
		                                 GetMutableDefault<UUnrealCSharpEditorSetting>());
	}
}

void FUnrealCSharpEditorSettingsHelper::UnregisterSettings()
{
	if ( ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings") )
	{
		SettingsModule->UnregisterSettings("Project",
		                                   "Plugins", "UnrealCSharpEditorSettings");
	}

	//FGeneratorCore::OnGetAdditionAssetsPaths.Remove()
}


#endif


#undef LOCTEXT_NAMESPACE
