#pragma once

#include "Reflection/Property/FPropertyDescriptor.h"

class FMapHelper final
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

	bool IsKeyPrimitiveProperty() const;

	bool IsValuePrimitiveProperty() const;

	FProperty* GetKeyProperty() const;

	FProperty* GetValueProperty() const;

	FScriptMap* GetScriptMap() const;

private:
	FPropertyDescriptor* KeyPropertyDescriptor;

	FPropertyDescriptor* ValuePropertyDescriptor;

	FScriptMap* ScriptMap;

	FScriptMapLayout ScriptMapLayout;

	bool bNeedFree;
};
