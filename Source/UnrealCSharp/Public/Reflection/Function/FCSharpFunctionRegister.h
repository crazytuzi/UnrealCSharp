#pragma once

#include "Reflection/Function/FCSharpFunctionOwnerClassInfo.h"

class UClass;

class FCSharpFunctionRegister
{
public:
#if WITH_OVERRIDE_BLUEPRINT_NATIVE_EVENT
	FCSharpFunctionRegister(UFunction* InFunction,
	                        UFunction* InOriginalFunction,
	                        const EFunctionFlags InOriginalFunctionFlags = FUNC_None,
	                        const FNativeFuncPtr InOriginalNativeFuncPtr = nullptr,
	                        const FCSharpFunctionOwnerClassInfo& InOwnerClassInfo = {});
#else
	FCSharpFunctionRegister(UFunction* InFunction,
	                        UFunction* InOriginalFunction,
	                        const EFunctionFlags InOriginalFunctionFlags = FUNC_None,
	                        const FNativeFuncPtr InOriginalNativeFuncPtr = nullptr);
#endif

	FCSharpFunctionRegister(const FCSharpFunctionRegister&) = default;

	FCSharpFunctionRegister(FCSharpFunctionRegister&& InOther);

	~FCSharpFunctionRegister();

public:
	const TWeakObjectPtr<UFunction>& GetOriginalFunction() const;

	EFunctionFlags GetOriginalFunctionFlags() const;

#if WITH_OVERRIDE_BLUEPRINT_NATIVE_EVENT
	static void IteratorRegister(const TFunctionRef<void(const FCSharpFunctionRegister&)>& InFunction);

	UClass* GetOriginalOwnerClass() const;

	void SuspendDummyOwnerClass() const;

	void ResumeDummyOwnerClass() const;

private:
	void AddRegister();

	void RemoveRegister() const;

private:
	static TSet<FCSharpFunctionRegister*> Registers;
#endif

private:
	TWeakObjectPtr<UFunction> Function;

	TWeakObjectPtr<UFunction> OriginalFunction;

	EFunctionFlags OriginalFunctionFlags;

	FNativeFuncPtr OriginalNativeFuncPtr;

#if WITH_OVERRIDE_BLUEPRINT_NATIVE_EVENT
	FCSharpFunctionOwnerClassInfo OwnerClassInfo;
#endif
};
