#pragma once

#include "Common/FUnrealCSharpFunctionLibrary.h"

template <typename T>
FString FGeneratorCore::GetFileName(const T* InField)
{
	FString ModuleName;

	FString DirectoryName;

	FString ModuleRelativeFile;

	if constexpr (std::is_same_v<T, FDelegateProperty> || std::is_same_v<T, FMulticastDelegateProperty>)
	{
		ModuleName = FPaths::Combine(
			InField->SignatureFunction->GetPackage()->GetName().StartsWith(TEXT("/Game"))
				? FApp::GetProjectName()
				: TEXT("")
			, FUnrealCSharpFunctionLibrary::GetClassNameSpace(InField)
			  .Replace(TEXT("."), TEXT("/"))
			  .Replace(TEXT("Script/"), TEXT("")));

		DirectoryName = FPaths::Combine(
			FUnrealCSharpFunctionLibrary::GetGenerationPath(InField->SignatureFunction), ModuleName);

		ModuleRelativeFile = FPaths::Combine(
			FPaths::GetPath(FGeneratorCore::GetModuleRelativePath(InField)),
			FUnrealCSharpFunctionLibrary::GetFullClass(InField));
	}
	else
	{
		ModuleName = FUnrealCSharpFunctionLibrary::GetModuleName(InField);

		DirectoryName = FPaths::Combine(FUnrealCSharpFunctionLibrary::GetGenerationPath(InField), ModuleName);

		ModuleRelativeFile = FPaths::Combine(
			FPaths::GetPath(FGeneratorCore::GetModuleRelativePath(InField)),
			InField->GetName());
	}

	return FPaths::Combine(DirectoryName, ModuleRelativeFile) + TEXT(".cs");
}
