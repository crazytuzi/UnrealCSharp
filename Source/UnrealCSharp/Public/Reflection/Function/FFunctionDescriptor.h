#pragma once

#include "Reflection/Property/FPropertyDescriptor.h"

class FFunctionDescriptor
{
public:
	explicit FFunctionDescriptor(UFunction* InFunction);

	virtual ~FFunctionDescriptor();

public:
	virtual void Initialize();

	virtual void Deinitialize();

public:
	virtual bool CallCSharp(FFrame& Stack, RESULT_DECL);

private:
	static FOutParmRec* FindOutParmRec(FOutParmRec* OutParam, const FProperty* OutProperty);

protected:
	// @TODO
	friend class FCSharpBind;

	TWeakObjectPtr<UFunction> Function;

	// @TODO
	TWeakObjectPtr<UFunction> OriginalFunction;

	TArray<FPropertyDescriptor*> PropertyDescriptors;

	FPropertyDescriptor* ReturnPropertyDescriptor;

	TArray<uint32> OutPropertyIndexes;
};
