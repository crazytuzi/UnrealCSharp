#pragma once

class FCSharpFunctionRegister
{
public:
	FCSharpFunctionRegister(UFunction* InFunction,
	                        UFunction* InOriginalFunction,
	                        const EFunctionFlags InOriginalFunctionFlags = FUNC_None,
	                        const FNativeFuncPtr InOriginalNativeFuncPtr = nullptr);

	FCSharpFunctionRegister(const FCSharpFunctionRegister&) = default;

	FCSharpFunctionRegister(FCSharpFunctionRegister&& InOther);

	~FCSharpFunctionRegister();

public:
	const TWeakObjectPtr<UFunction>& GetOriginalFunction() const;

	EFunctionFlags GetOriginalFunctionFlags() const;

private:
	TWeakObjectPtr<UFunction> Function;

	TWeakObjectPtr<UFunction> OriginalFunction;

	EFunctionFlags OriginalFunctionFlags;

	FNativeFuncPtr OriginalNativeFuncPtr;
};
