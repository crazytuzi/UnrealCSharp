#pragma once

#include "Common/FUnrealCSharpFunctionLibrary.h"

template <typename T>
FString FGeneratorCore::GetFileName(const T* InField)
{
	if constexpr (std::is_same_v<T, FDelegateProperty> || std::is_same_v<T, FMulticastDelegateProperty>)
	{
		FString RelativeModuleName;
		
		const auto SignatureFunction = InField->SignatureFunction;

		if (SignatureFunction == nullptr)
		{
			RelativeModuleName = TEXT("");
		}

		if (const auto Class = Cast<UClass>(SignatureFunction->GetOuter()))
		{
			if (InField->IsNative())
			{
				RelativeModuleName = FString::Printf(TEXT(
					"%s/%s"
				),
									   *(Class->GetOuter() ? Class->GetOuter()->GetName() : TEXT("")),
									   *Class->GetName());
			}
			else
			{
				RelativeModuleName = *(Class->GetOuter() ? Class->GetOuter()->GetName() : TEXT(""));
			}
		}

		if (const auto Package = Cast<UPackage>(SignatureFunction->GetOuter()))
		{
			RelativeModuleName = Package->GetName().Replace(TEXT("/Script/"), TEXT("/"));
		}

		if (!InField->IsNative())
		{
			auto Index = 0;

			if (RelativeModuleName.FindLastChar(TEXT('/'), Index))
			{
				RelativeModuleName.LeftInline(Index);
			}
		}

		auto ModuleName = FUnrealCSharpFunctionLibrary::GetModuleName(RelativeModuleName);

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

		auto DirectoryName = FPaths::Combine(FUnrealCSharpFunctionLibrary::GetGenerationPath(InField), ModuleName);

		auto ModuleRelativeFile = FPaths::Combine(
			FPaths::GetPath(FGeneratorCore::GetModuleRelativePath(InField)),
			InField->GetName());

		return FPaths::Combine(DirectoryName, ModuleRelativeFile) + TEXT(".cs");
	}
}
