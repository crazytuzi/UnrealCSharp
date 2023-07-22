#pragma once

#include "FBindingFunctionBase.inl"
#include "FFunctionInfo.h"

struct FBindingFunction : FBindingFunctionBase
{
	FBindingFunction() = default;

	FBindingFunction(FFunctionInfo* InInfo, const FString& InName,
	                 const FString& InImplementationName, const TArray<FString>& InParamNames):
		FBindingFunctionBase(InName, InImplementationName),
		Info(InInfo),
		ParamNames(InParamNames)
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
		return ParamNames;
	}

private:
	FFunctionInfo* Info;

	TArray<FString> ParamNames;
};
