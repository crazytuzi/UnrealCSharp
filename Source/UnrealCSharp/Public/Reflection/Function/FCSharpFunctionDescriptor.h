#pragma once

#include "FFunctionDescriptor.h"

class FCSharpFunctionDescriptor final : public FFunctionDescriptor
{
public:
	typedef FFunctionDescriptor Super;

public:
	explicit FCSharpFunctionDescriptor(UFunction* InFunction);

	virtual ~FCSharpFunctionDescriptor() override;

public:
	virtual void Deinitialize() override;

public:
	bool CallCSharp(const FFrame& InStack);

private:
	static FOutParmRec* FindOutParmRec(FOutParmRec* OutParam, const FProperty* OutProperty);

private:
	friend class FCSharpBind;

	TWeakObjectPtr<UFunction> OriginalFunction;

	EFunctionFlags OriginalFunctionFlags;

	FNativeFuncPtr OriginalNativeFuncPtr;

	TArray<uint8> OriginalScript;
};
