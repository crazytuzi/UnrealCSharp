#pragma once

#include "Common/FUnrealCSharpFunctionLibrary.h"

template <typename T>
FString FGeneratorCore::GetFileName(const T* InField)
{
	if constexpr (std::is_same_v<T, FDelegateProperty> || std::is_same_v<T, FMulticastDelegateProperty>)
	{
		auto ModuleName = FPaths::Combine(
			InField->SignatureFunction->GetPackage()->GetName().StartsWith(TEXT("/Game"))
				? FApp::GetProjectName()
				: TEXT(""),
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(InField)
			.Replace(TEXT("."), TEXT("/"))
			.Replace(TEXT("Script/"), TEXT("")));

		auto DirectoryName = FPaths::Combine(
			FUnrealCSharpFunctionLibrary::GetGenerationPath(InField->SignatureFunction), ModuleName);

		auto ModuleRelativeFile = FPaths::Combine(
			FPaths::GetPath(FGeneratorCore::GetModuleRelativePath(InField)),
			FUnrealCSharpFunctionLibrary::GetFullClass(InField));

		return FPaths::Combine(DirectoryName, ModuleRelativeFile) + TEXT(".cs");
	}
	else
	{
		auto ModuleName = FUnrealCSharpFunctionLibrary::GetModuleName(InField);

		auto DirectoryName = FPaths::Combine(
			FUnrealCSharpFunctionLibrary::GetGenerationPath(InField), ModuleName);

		auto ModuleRelativeFile = FPaths::Combine(
			FPaths::GetPath(FGeneratorCore::GetModuleRelativePath(InField)),
			InField->GetName());

		return FPaths::Combine(DirectoryName, ModuleRelativeFile) + TEXT(".cs");
	}
}
