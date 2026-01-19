#include "Domain/AssemblyLoader.h"
#include "Misc/FileHelper.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/Macro.h"

TArray<uint8> UAssemblyLoader::Load(const FString& InAssemblyName)
{
	auto AssemblyPaths = FUnrealCSharpFunctionLibrary::GetAssemblyPath();

	for (const auto& AssemblyPath : AssemblyPaths)
	{
		if (const auto File = FPaths::Combine(AssemblyPath, InAssemblyName) + DLL_SUFFIX;
			IFileManager::Get().FileExists(*File))
		{
			TArray<uint8> Data;

			FFileHelper::LoadFileToArray(Data, *File);

			return Data;
		}
	}

	return {};
}
