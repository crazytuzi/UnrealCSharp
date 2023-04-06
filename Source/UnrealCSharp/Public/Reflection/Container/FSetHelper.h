﻿#pragma once

#include "FContainerHelper.h"
#include "Reflection/Property/FPropertyDescriptor.h"

class FSetHelper final : public FContainerHelper
{
public:
	explicit FSetHelper(FProperty* InProperty, void* InData = nullptr);

	~FSetHelper();

public:
	void Initialize();

	void Deinitialize();

public:
	void Empty(int32 InExpectedNumElements) const;
	
	int32 Num() const;

	void Add(void* InValue) const;
	
	int32 Remove(const void* InValue) const;
	
	bool Contains(const void* InKey) const;

	TArray<FProperty*> ToArray() const;
	
	void Find(int32 SetIndex,void* InValue) const;
	
	int32 GetMaxIndex() const;
	
	TSet<void*> Union(TSet<void*> OtherSet) const;
	
	FProperty* GetElementProperty() const;

	FScriptSet* GetScriptSet() const;

	FORCEINLINE FScriptSetHelper CreateHelperFormElementProperty() const
	{
		return FScriptSetHelper::CreateHelperFormElementProperty(ElementPropertyDescriptor->GetProperty(), ScriptSet);
	}

private:
	
	FPropertyDescriptor* ElementPropertyDescriptor;

	FScriptSet* ScriptSet;

	FScriptSetLayout ScriptSetLayout;

	bool bNeedFree;
};
