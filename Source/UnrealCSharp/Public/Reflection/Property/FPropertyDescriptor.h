#pragma once

class FPropertyDescriptor
{
public:
	static FPropertyDescriptor* Factory(FProperty* InProperty);

public:
	virtual ~FPropertyDescriptor() = default;

public:
	template <typename BoolConstant>
	auto Get(void* Src, void** Dest) const;

	virtual void Get(void* Src, void** Dest) const;

	virtual void Get(void* Src, void** Dest, std::true_type) const;

	virtual void Get(void* Src, void** Dest, std::false_type) const;

	virtual void Get(void* Src, void* Dest) const;

	virtual void Set(void* Src, void* Dest) const;

public:
	virtual FProperty* GetProperty() const;

	virtual void* CopyValue(const void* InAddress) const;

	virtual void DestroyProperty();

public:
	FORCEINLINE int32 GetElementSize() const;

	FORCEINLINE EPropertyFlags GetPropertyFlags() const;

	virtual bool Identical(const void* A, const void* B, uint32 PortFlags = 0) const;

	template <typename ValueType>
	FORCEINLINE auto ContainerPtrToValuePtr(void* ContainerPtr, const int32 ArrayIndex = 0) const;

	virtual void DestroyValue(void* Dest) const;

	FORCEINLINE FString GetName() const;

	FORCEINLINE void InitializeValue_InContainer(void* Dest) const;

	FORCEINLINE int32 GetSize() const;

	FORCEINLINE int32 GetMinAlignment() const;

	FORCEINLINE uint32 GetValueTypeHash(const void* Src) const;

	FORCEINLINE bool SameType(const FPropertyDescriptor* Other) const;

	virtual bool IsPrimitiveProperty() const;
};

#include "FPropertyDescriptor.inl"
