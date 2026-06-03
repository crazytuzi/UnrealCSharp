#pragma once

#include "FManagedFunctionDescriptor.h"
#include "FCSharpFunctionRegister.h"

class FCSharpFunctionDescriptor final : public FManagedFunctionDescriptor
{
public:
	typedef FManagedFunctionDescriptor Super;

public:
	explicit FCSharpFunctionDescriptor(UFunction* InFunction, FCSharpFunctionRegister&& InFunctionRegister);

public:
	bool CallCSharp(UObject* InContext, FFrame& InStack, RESULT_DECL);

public:
	const TWeakObjectPtr<UFunction>& GetOriginalFunction() const;

private:
	static FOutParmRec* FindOutParmRec(FOutParmRec* OutParam, const FProperty* OutProperty);

private:
	FCSharpFunctionRegister FunctionRegister;

	FMethodReflection* Method{};
};
