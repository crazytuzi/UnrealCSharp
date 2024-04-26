#pragma once

#include "FFunctionInfo.h"
#include "EFunctionInteract.h"

struct FBindingFunction
{
	FBindingFunction() = default;

	FBindingFunction(const FString& InName, const FString& InImplementationName, FFunctionInfo* InFunctionInfo):
		Name(InName),
		ImplementationName(InImplementationName),
		FunctionInfo(InFunctionInfo)
	{
	}

	const FString& GetFunctionName() const
	{
		return Name;
	}

	const FString& GetFunctionImplementationName() const
	{
		return ImplementationName;
	}

	bool IsSet() const
	{
		return FunctionInfo != nullptr;
	}

	bool IsConstructor() const
	{
		return FunctionInfo != nullptr ? FunctionInfo->IsConstructor() : false;
	}

	bool IsDestructor() const
	{
		return FunctionInfo != nullptr ? FunctionInfo->IsDestructor() : false;
	}

	bool IsStatic() const
	{
		return FunctionInfo != nullptr ? FunctionInfo->IsStatic() : false;
	}

	FTypeInfo* GetReturn() const
	{
		return FunctionInfo != nullptr ? FunctionInfo->GetReturn() : nullptr;
	}

	const TArray<FTypeInfo*>& GetParams() const
	{
		static TArray<FTypeInfo*> Instance;

		return FunctionInfo != nullptr ? FunctionInfo->GetParams() : Instance;
	}

	const TArray<FString>& GetParamNames() const
	{
		static TArray<FString> Instance;

		return FunctionInfo != nullptr ? FunctionInfo->GetParamNames() : Instance;
	}

	const TArray<FString>& GetDefaultArguments() const
	{
		static TArray<FString> Instance;

		return FunctionInfo != nullptr ? FunctionInfo->GetDefaultArguments() : Instance;
	}

	EFunctionInteract GetFunctionInteract() const
	{
		return FunctionInfo != nullptr ? FunctionInfo->GetFunctionInteract() : EFunctionInteract::None;
	}

private:
	FString Name;

	FString ImplementationName;

	FFunctionInfo* FunctionInfo;
};
