#pragma once

struct FBindingMethod
{
	FBindingMethod() = default;

	FBindingMethod(const FString& InMethod, const void* InFunction, const int32 InParamCount = INDEX_NONE) :
		Method(InMethod),
		Function(InFunction),
		ParamCount(InParamCount)
	{
	}

	const FString& GetMethod() const
	{
		return Method;
	}

	const void* GetFunction() const
	{
		return Function;
	}

	int32 GetParamCount() const
	{
		return ParamCount;
	}

private:
	FString Method;

	const void* Function;

	int32 ParamCount{INDEX_NONE};
};
