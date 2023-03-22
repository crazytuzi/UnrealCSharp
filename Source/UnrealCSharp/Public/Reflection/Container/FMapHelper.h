#pragma once

#include "FContainerHelper.h"
#include "Reflection/Property/FPropertyDescriptor.h"

class FMapHelper final : public FContainerHelper
{
public:
	explicit FMapHelper(FProperty* InKeyProperty, FProperty* InValueProperty, void* InData = nullptr);

	~FMapHelper();

public:
	void Initialize();

	void Deinitialize();

public:
	void Empty(int32 InExpectedNumElements) const;

	int32 Num() const;

	void Add(void* InKey, void* InValue) const;

	int32 Remove(const void* InKey) const;

	void* FindKey(const void* InValue) const;

	void* Find(const void* InKey) const;

	bool Contains(const void* InKey) const;

	void* Get(const void* InKey) const;

	void Set(void* InKey, void* InValue) const;

	FPropertyDescriptor* GetKeyPropertyDescriptor() const;

	FPropertyDescriptor* GetValuePropertyDescriptor() const;

	FScriptMap* GetScriptMap() const;

	int32 GetMaxIndex() const;

	bool IsValidIndex(int32 InIndex) const;

	void* GetEnumeratorKey(int32 InIndex) const;

	void* GetEnumeratorValue(int32 InIndex) const;

private:
	FPropertyDescriptor* KeyPropertyDescriptor;

	FPropertyDescriptor* ValuePropertyDescriptor;

	FScriptMap* ScriptMap;

	FScriptMapLayout ScriptMapLayout;

	bool bNeedFree;
};
