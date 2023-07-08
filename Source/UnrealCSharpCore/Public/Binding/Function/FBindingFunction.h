#pragma once

#include "FFunctionInfo.h"

struct FBindingFunction
{
	FBindingFunction() = default;

	FBindingFunction(FFunctionInfo* InInfo, const FString& InName):
		Name(InName),
		Info{InInfo}
	{
	}

	FString GetFunctionName() const
	{
		return Name;
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

private:
	FString Name;

	FFunctionInfo* Info;
};
