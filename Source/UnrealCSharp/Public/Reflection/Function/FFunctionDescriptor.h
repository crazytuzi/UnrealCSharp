#pragma once

#include "mono/metadata/object.h"
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
	FName GetFName() const;

public:
	bool CallCSharp(const FFrame& InStack);

	MonoObject* CallUnreal(UObject* InObject, MonoObject** OutValue, MonoArray* InValue);

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

	TArray<uint32> ReferencePropertyIndexes;

	TArray<uint32> OutPropertyIndexes;

	void* Params;
};
