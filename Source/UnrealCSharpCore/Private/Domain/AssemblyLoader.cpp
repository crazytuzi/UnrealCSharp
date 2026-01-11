#include "Domain/AssemblyLoader.h"
#include "CoreMacro/Macro.h"
#include "Domain/FMonoFunctionLibrary.h"
#include "Misc/FileHelper.h"

TArray<uint8> UAssemblyLoader::Load(const FString& InAssemblyName)
{
	const auto Directory = FMonoFunctionLibrary::GetNetDirectory();

	const auto File = FPaths::Combine(Directory, InAssemblyName) + DLL_SUFFIX;

	TArray<uint8> Data;

	FFileHelper::LoadFileToArray(Data, *File);

	return Data;
}
