#pragma once

struct FBindingFunctionBase
{
	FBindingFunctionBase() = default;

	FBindingFunctionBase(const FString& InName, const FString& InImplementationName):
		Name(InName),
		ImplementationName(InImplementationName)
	{
	}

	FString GetFunctionName() const
	{
		return Name;
	}

	FString GetFunctionImplementationName() const
	{
		return ImplementationName;
	}

private:
	FString Name;

	FString ImplementationName;
};

inline bool operator==(const FBindingFunctionBase& A, const FBindingFunctionBase& B)
{
	return A.GetFunctionImplementationName() == B.GetFunctionImplementationName();
}

static uint32 GetTypeHash(const FBindingFunctionBase& InBindingFunctionBase)
{
	return GetTypeHash(InBindingFunctionBase.GetFunctionImplementationName());
}
