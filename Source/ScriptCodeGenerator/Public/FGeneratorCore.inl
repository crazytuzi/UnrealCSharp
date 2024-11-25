#pragma once

#include "UEVersion.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/Macro.h"

template <typename T>
auto FGeneratorCore::GetFileName(const T* InField)
{
	if constexpr (std::is_same_v<T, FDelegateProperty> || std::is_same_v<T, FMulticastDelegateProperty>)
	{
		const auto SignatureFunction = InField->SignatureFunction;

		if (SignatureFunction == nullptr)
		{
			return FString();
		}

		auto ModuleName = FUnrealCSharpFunctionLibrary::GetModuleName(SignatureFunction);

		auto DirectoryName = FPaths::Combine(
			FUnrealCSharpFunctionLibrary::GetGenerationPath(SignatureFunction), ModuleName);

		auto ModuleRelativePath = FUnrealCSharpFunctionLibrary::GetModuleRelativePath(InField);

		auto FileName = FUnrealCSharpFunctionLibrary::GetFullClass(InField) + CSHARP_SUFFIX;

		return FPaths::Combine(DirectoryName, ModuleRelativePath, FileName);
	}
	else
	{
		auto ModuleName = FUnrealCSharpFunctionLibrary::GetModuleName(InField);

		auto DirectoryName = FPaths::Combine(
			FUnrealCSharpFunctionLibrary::GetGenerationPath(InField), ModuleName);

		auto ModuleRelativePath = FUnrealCSharpFunctionLibrary::GetModuleRelativePath(InField);

		auto FileName = InField->GetName() + CSHARP_SUFFIX;

		return FPaths::Combine(DirectoryName, ModuleRelativePath, FileName);
	}
}
