#include "FGeneratorPaths.h"

#include "Misc/FileHelper.h"
#include "Windows/LiveCoding/Public/ILiveCodingModule.h"

FString FGeneratorPaths::GetManagedBaseName()
{
	return TEXT("Script");
}

FString FGeneratorPaths::GetManagedBasePath()
{
	return FPaths::Combine(FPaths::ProjectDir(), GetManagedBaseName());
}

FString FGeneratorPaths::GetUEManagedProjectName()
{
	return TEXT("UE-Managed");
}

FString FGeneratorPaths::GetUEManagedPath()
{
	return FPaths::Combine(GetManagedBasePath(), GetUEManagedProjectName());
}

FString FGeneratorPaths::GetUEManagedProxyPath()
{
	return FPaths::Combine(GetUEManagedPath(), TEXT("Proxy"));
}

FString FGeneratorPaths::GetGameManagedProjectName()
{
	return TEXT("Game-Managed");
}

FString FGeneratorPaths::GetGameManagedPath()
{
	return FPaths::Combine(GetManagedBasePath(), GetGameManagedProjectName());
}

FString FGeneratorPaths::GetGameManagedProxyPath()
{
	return FPaths::Combine(GetGameManagedPath(), TEXT("Proxy"));
}


static TArray<FString>& GetGameModuleList()
{
	static TArray<FString> GameModuleList;

	if(GameModuleList.IsEmpty())
	{
		ILiveCodingModule* LiveCoding = static_cast<ILiveCodingModule*>(FModuleManager::Get().LoadModule(TEXT("LiveCoding")));

		if(LiveCoding)
		{
			LiveCoding->GetOnPatchCompleteDelegate().AddLambda([]()
			{
				GameModuleList.Empty();
			});
		}
		
		// Scan
		auto TxtFile = FPaths::Combine(FPaths::ProjectPluginsDir(), TEXT("UnrealCSharp"), TEXT("Intermediate"), TEXT("GameModules.txt"));

		FFileHelper::LoadFileToStringArray(GameModuleList, *TxtFile);

		GameModuleList.Add(TEXT("Game"));
	}
	
	return GameModuleList;
}


FString FGeneratorPaths::GetGenerationPath(const FString& InternalScriptPath)
{
	check(!InternalScriptPath.IsEmpty() && InternalScriptPath[0] == TEXT('/'));
	
	TArray<FString> Splits;
	
	InternalScriptPath.ParseIntoArray(Splits, TEXT("/"));

	auto& GameModuleList = GetGameModuleList();
	
	if( GameModuleList.Contains(Splits[0])  ||  (Splits[0] == TEXT("Script") && GameModuleList.Contains(Splits[1])) )
	{
		return GetGameManagedProxyPath();
	}
	else
	{
		return GetUEManagedProxyPath();
	}
}
