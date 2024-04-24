#pragma once

#include "FBindingFunctionBase.inl"
#include "FFunctionInfo.h"
#include "EFunctionInteract.h"

struct FBindingFunction : FBindingFunctionBase
{
	FBindingFunction() = default;

	FBindingFunction(FFunctionInfo* InInfo, const FString& InName, const FString& InImplementationName):
		FBindingFunctionBase(InName, InImplementationName),
		Info(InInfo)
	{
	}

	bool IsConstructor() const
	{
		return Info != nullptr ? Info->IsConstructor() : false;
	}

	bool IsDestructor() const
	{
		return Info != nullptr ? Info->IsDestructor() : false;
	}

	bool IsStatic() const
	{
		return Info != nullptr ? Info->IsStatic() : false;
	}

	FTypeInfo* GetReturn() const
	{
		return Info != nullptr ? Info->GetReturn() : nullptr;
	}

	const TArray<FTypeInfo*>& GetParams() const
	{
		static TArray<FTypeInfo*> Instance;

		return Info != nullptr ? Info->GetParams() : Instance;
	}

	const TArray<FString>& GetParamNames() const
	{
		static TArray<FString> Instance;

		return Info != nullptr ? Info->GetParamNames() : Instance;
	}

	const TArray<FString>& GetDefaultArguments() const
	{
		static TArray<FString> Instance;

		return Info != nullptr ? Info->GetDefaultArguments() : Instance;
	}

	EFunctionInteract GetFunctionInteract() const
	{
		return Info != nullptr ? Info->GetFunctionInteract() : EFunctionInteract::None;
	}

private:
	FFunctionInfo* Info;
};
