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

		auto ModuleRelativePath = FPaths::Combine(
			FUnrealCSharpFunctionLibrary::GetModuleRelativePath(InField),
			FUnrealCSharpFunctionLibrary::GetFullClass(InField));

		return FPaths::Combine(DirectoryName, ModuleRelativePath) + CSHARP_SUFFIX;
	}
	else
	{
		auto ModuleName = FUnrealCSharpFunctionLibrary::GetModuleName(InField);

		auto DirectoryName = FPaths::Combine(
			FUnrealCSharpFunctionLibrary::GetGenerationPath(InField), ModuleName);

		auto ModuleRelativePath = FPaths::Combine(
			FUnrealCSharpFunctionLibrary::GetModuleRelativePath(InField),
			InField->GetName());

		return FPaths::Combine(DirectoryName, ModuleRelativePath) + CSHARP_SUFFIX;
	}
}
