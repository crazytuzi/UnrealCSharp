#include "Domain/Mono/AssemblyLoader.h"
#if WITH_MONO
#include "Misc/FileHelper.h"
#include "CoreMacro/Macro.h"
#include "Domain/Mono/FMonoFunctionLibrary.h"
#endif

TArray<uint8> UAssemblyLoader::Load(const FString& InAssemblyName)
{
#if WITH_MONO
	const auto AssemblyPaths = FMonoFunctionLibrary::GetAssemblyPath();

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
#endif

	return {};
}
