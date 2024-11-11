#pragma once

#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/Macro.h"

template <typename T>
auto FGeneratorCore::GetFileName(const T* InField)
{
	if constexpr (std::is_same_v<T, FDelegateProperty> || std::is_same_v<T, FMulticastDelegateProperty>)
	{
		FString RelativeModuleName;

		const auto SignatureFunction = InField->SignatureFunction;

		FString ModuleName;

		if (const auto Class = Cast<UClass>(SignatureFunction->GetOuter()))
		{
			ModuleName = FUnrealCSharpFunctionLibrary::GetModuleName(
				Class->GetOuter() ? Class->GetOuter()->GetName() : TEXT(""));
		}

		if (const auto Package = Cast<UPackage>(SignatureFunction->GetOuter()))
		{
			ModuleName = FUnrealCSharpFunctionLibrary::GetModuleName(Package);
		}

		auto DirectoryName = FPaths::Combine(
			FUnrealCSharpFunctionLibrary::GetGenerationPath(SignatureFunction), ModuleName);

		auto ModuleRelativeFile = FPaths::Combine(
			FPaths::GetPath(FUnrealCSharpFunctionLibrary::GetModuleRelativePath(InField)),
			FUnrealCSharpFunctionLibrary::GetFullClass(InField));

		return FPaths::Combine(DirectoryName, ModuleRelativeFile) + CSHARP_SUFFIX;
	}
	else
	{
		auto ModuleName = FUnrealCSharpFunctionLibrary::GetModuleName(InField);

		auto DirectoryName = FPaths::Combine(
			FUnrealCSharpFunctionLibrary::GetGenerationPath(InField), ModuleName);

		auto ModuleRelativeFile = FPaths::Combine(
			FUnrealCSharpFunctionLibrary::GetModuleRelativePath(InField),
			InField->GetName());

		return FPaths::Combine(DirectoryName, ModuleRelativeFile) + CSHARP_SUFFIX;
	}
}
