#pragma once

#include "Reflection/Property/FPropertyDescriptor.h"

class UNREALCSHARP_API FArrayHelper
{
public:
	explicit FArrayHelper(FProperty* InProperty, void* InData,
	                      bool InbNeedFreeData, bool InbNeedFreeProperty);

	~FArrayHelper();

public:
	void Initialize();

	void Deinitialize();

public:
	static bool Identical(const FArrayHelper* InA, const FArrayHelper* InB);

	int32 GetTypeSize() const;

	int32 GetSlack() const;

	bool IsValidIndex(int32 InIndex) const;

	int32 Num() const;

	bool IsEmpty() const;

	int32 Max() const;

	void* Get(int32 Index) const;

	void Set(int32 Index, void* InValue) const;

	int32 Find(const void* InValue) const;

	int32 FindLast(const void* InValue) const;

	bool Contains(const void* InValue) const;

	int32 AddUninitialized(int32 InCount) const;

	void InsertZeroed(int32 InIndex, int32 InCount) const;

	void InsertDefaulted(int32 InIndex, int32 InCount) const;

	void RemoveAt(int32 InIndex, const int32 InCount, const bool bAllowShrinking) const;

	void Reset(int32 InNewSize) const;

	void Empty(int32 InSlack) const;

	void SetNum(int32 InNewNum, bool bAllowShrinking) const;

	int32 Add(void* InValue) const;

	int32 AddZeroed(int32 InCount) const;

	int32 AddUnique(void* InValue) const;

	int32 RemoveSingle(const void* InValue) const;

	int32 Remove(const void* InValue) const;

	void SwapMemory(int32 InFirstIndexToSwap, int32 InSecondIndexToSwap) const;

	void Swap(int32 InFirstIndexToSwap, int32 InSecondIndexToSwap) const;

	FPropertyDescriptor* GetInnerPropertyDescriptor() const;

	FScriptArray* GetScriptArray() const;

	FORCEINLINE FScriptArrayHelper CreateHelperFormInnerProperty() const
	{
		return FScriptArrayHelper::CreateHelperFormInnerProperty(InnerPropertyDescriptor->GetProperty(), ScriptArray);
	}

private:
	FPropertyDescriptor* InnerPropertyDescriptor;

	FScriptArray* ScriptArray;

	bool bNeedFreeData;

	bool bNeedFreeProperty;
};
