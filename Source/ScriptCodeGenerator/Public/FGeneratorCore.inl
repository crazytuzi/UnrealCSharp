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

		FString ModuleName;

		auto ModuleRelativePath = FUnrealCSharpFunctionLibrary::GetModuleRelativePath(
			SignatureFunction, InField->IsNative());

		if (const auto Class = Cast<UClass>(SignatureFunction->GetOuter()))
		{
			ModuleName = FUnrealCSharpFunctionLibrary::GetModuleName(ModuleRelativePath);
		}
		else if (const auto Package = Cast<UPackage>(SignatureFunction->GetOuter()))
		{
			ModuleName = FUnrealCSharpFunctionLibrary::GetModuleName(Package);
		}

		auto DirectoryName = FPaths::Combine(
			FUnrealCSharpFunctionLibrary::GetGenerationPath(SignatureFunction), ModuleName);

		if (!InField->IsNative())
		{
			if (auto Index = 0; ModuleRelativePath.FindLastChar(TEXT('/'), Index))
			{
				ModuleRelativePath.LeftInline(Index);
			}
		}

		auto ModuleRelativeFile = FPaths::Combine(
			FUnrealCSharpFunctionLibrary::GetModuleRelativePath(
				FPaths::GetPath(InField->GetMetaData(TEXT("ModuleRelativePath")))),
			FUnrealCSharpFunctionLibrary::GetFullClass(InField));

		return FPaths::Combine(DirectoryName, FPaths::Combine(ModuleRelativePath, ModuleRelativeFile)) + CSHARP_SUFFIX;
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
