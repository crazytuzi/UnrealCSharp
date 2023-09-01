#include "UnrealCSharpEditor/Public/Setting/UnrealCSharpSetting.h"

#include "FGeneratorCore.h"
#include "ISettingsContainer.h"
#include "ISettingsModule.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Misc/MonitoredProcess.h"

#define LOCTEXT_NAMESPACE "FUnrealCSharpEditorSettings"

TArray<FString> FUnrealCSharpSettingsHelper::LogOutPutMessage = {};

TArray<FString> UUnrealCSharp_Settings::GetDotNetPath() const
{
	// https://learn.microsoft.com/en-us/dotnet/core/install/how-to-detect-installed-versions?pivots=os-windows
	const FString RunCommand = TEXT("dotnet");
	const FString Parms = TEXT("--list-sdks");

	const TSharedPtr<FMonitoredProcess> RunProcess =
		MakeShareable(new FMonitoredProcess(RunCommand, Parms,true));
	FString OutputMessage = TEXT("");

	FUnrealCSharpSettingsHelper::LogOutPutMessage.Empty();
	RunProcess->OnOutput().BindStatic(&FUnrealCSharpSettingsHelper::OnStatusOutput); 
	RunProcess->Launch(); 
	while(RunProcess->Update()) 
	{ 
		FPlatformProcess::Sleep(0.01f); 
	}

	TArray<FString> ResultPathArray;

	if ( FUnrealCSharpSettingsHelper::LogOutPutMessage.Num() >0 )
	{
		// 需要匹配 3.1.424 [C:\program files\dotnet\sdk]  这样的字符串
		// 这里简单检测一下,
		// 1. 提取第一个空格前的字符串,通过 . 来分割,如果分割后的数组长度大于等于3并且是数字,则认为是正确版本号 否则直接返回默认路径
		for ( auto Command : FUnrealCSharpSettingsHelper::LogOutPutMessage )
		{
			int SpaceIndex = 0;
			const auto FindResult = Command.FindChar(' ',SpaceIndex);
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
					PathStr = PathStr.TrimStartAndEnd();
					// 去除前后括号[] 把 \ 转换成 / 并且去除最后的 sdk 路径 加上 dotnet.exe
					PathStr = PathStr[0] == '[' ? PathStr.Right(PathStr.Len() - 1) : PathStr;
					PathStr = PathStr[PathStr.Len() - 1] == ']' ? PathStr.Left(PathStr.Len() - 1) : PathStr;
					PathStr = PathStr.Replace(TEXT("\\"),TEXT("/"));
					PathStr = PathStr.EndsWith(TEXT("sdk")) ? PathStr.Left(PathStr.Len() - 3) : PathStr;\
					PathStr = PathStr + TEXT("dotnet.exe");
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


#if WITH_EDITOR


void UUnrealCSharp_Settings::PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent)
{
	Super::PostEditChangeChainProperty(PropertyChangedEvent);
	if (PropertyChangedEvent.GetPropertyName() == TEXT("DotNetPath"))
	{
		FUnrealCSharpFunctionLibrary::DotNetPath = DotNetPath;
	}
	else if ( PropertyChangedEvent.GetPropertyName() == TEXT("GenSourcePath") )
	{
		// 由于这里只会相应数组数量改变,不会响应里面的值改变,所以这里不处理
	}
}

void FUnrealCSharpSettingsHelper::RegisterSettings()
{
	// 项目设置
	if ( ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings") )
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "UUnrealCSharp_Settings",
										 LOCTEXT("UnrealCSharpEditorSettingsName", "UnrealCSharp Setting"),
										 LOCTEXT("UnrealCSharpEditorSettingsDescription", "UnrealCSharp Setting"),
										 GetMutableDefault<UUnrealCSharp_Settings>());
	}

	FGeneratorCore::OnGetAdditionAssetsPaths.AddStatic(FUnrealCSharpSettingsHelper::GetAllAdditionAssetsPaths);
}

void FUnrealCSharpSettingsHelper::UnregisterSettings()
{
	if ( ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings") )
	{
		SettingsModule->UnregisterSettings("Project",
			"Plugins", "UUnrealCSharp_Settings");
	}

	//FGeneratorCore::OnGetAdditionAssetsPaths.Remove()
}


#endif


void FUnrealCSharpSettingsHelper::GetAllAdditionAssetsPaths(TArray<FName>& PathArray)
{
	const auto& CommandletSettings = *GetMutableDefault<UUnrealCSharp_Settings>();
	for ( auto Element : CommandletSettings.GenSourcePath )
	{
		if ( Element.Path.Len() > 0 )
		{
			auto TempPath = TEXT("/Game/") + Element.Path;
			FName PathName = FName(*TempPath);
			PathArray.Add(PathName);
		}
	}
}

#undef LOCTEXT_NAMESPACE