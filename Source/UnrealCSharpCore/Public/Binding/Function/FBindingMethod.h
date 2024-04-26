#pragma once

struct FBindingMethod
{
	FBindingMethod() = default;

	FBindingMethod(const FString& InMethod, const void* InFunction):
		Method(InMethod),
		Function(InFunction)
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

private:
	FString Method;

	const void* Function;
};
