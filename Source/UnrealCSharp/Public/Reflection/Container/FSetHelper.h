#pragma once

#include "Reflection/Property/FPropertyDescriptor.h"

class UNREALCSHARP_API FSetHelper
{
public:
	explicit FSetHelper(FProperty* InProperty, void* InData,
	                    bool InbNeedFreeData, bool InbNeedFreeProperty);

	~FSetHelper();

public:
	void Initialize();

	void Deinitialize();

public:
	void Empty(int32 InExpectedNumElements) const;

	int32 Num() const;

	bool IsEmpty() const;

	int32 GetMaxIndex() const;

	void Add(void* InValue) const;

	int32 Remove(const void* InValue) const;

	bool Contains(const void* InValue) const;

	FPropertyDescriptor* GetElementPropertyDescriptor() const;

	FScriptSet* GetScriptSet() const;

	bool IsValidIndex(int32 InIndex) const;

	void* GetEnumerator(int32 InIndex) const;

private:
	FPropertyDescriptor* ElementPropertyDescriptor;

	FScriptSet* ScriptSet;

	FScriptSetLayout ScriptSetLayout;

	bool bNeedFreeData;

	bool bNeedFreeProperty;
};
