#pragma once

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

		FString ModuleRelativeName = FUnrealCSharpFunctionLibrary::GetModuleRelativePath(InField);

		if (const auto Class = Cast<UClass>(SignatureFunction->GetOuter()))
		{
			ModuleName = FUnrealCSharpFunctionLibrary::GetModuleName(ModuleRelativeName);
		}

		if (const auto Package = Cast<UPackage>(SignatureFunction->GetOuter()))
		{
			ModuleName = FUnrealCSharpFunctionLibrary::GetModuleName(Package);
		}

		auto DirectoryName = FPaths::Combine(
			FUnrealCSharpFunctionLibrary::GetGenerationPath(SignatureFunction), ModuleName);

		if (!InField->IsNative())
		{
			if (auto Index = 0; ModuleRelativeName.FindLastChar(TEXT('/'), Index))
			{
				ModuleRelativeName.LeftInline(Index);
			}
		}

		auto ModuleRelativePathMetaData = FPaths::Combine(
			FUnrealCSharpFunctionLibrary::GetModuleRelativePath(FPaths::GetPath(InField->GetMetaData(TEXT("ModuleRelativePath")))),
			FUnrealCSharpFunctionLibrary::GetFullClass(InField));

		ModuleRelativeName = FPaths::Combine(ModuleRelativeName, ModuleRelativePathMetaData);
		
		return FPaths::Combine(DirectoryName, ModuleRelativeName) + CSHARP_SUFFIX;
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
