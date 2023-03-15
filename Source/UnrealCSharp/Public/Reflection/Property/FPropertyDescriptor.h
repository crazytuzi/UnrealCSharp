#pragma once

class FPropertyDescriptor
{
public:
	static EPropertyType GetPropertyType(const FProperty* Property);

	static FPropertyDescriptor* Factory(FProperty* InProperty);

public:
	virtual ~FPropertyDescriptor() = default;

	explicit FPropertyDescriptor(FProperty* InProperty);

public:
	virtual void Get(void* Src, void** Dest) const;

	virtual void Get(void* Src, void* Dest) const;

	virtual void Set(void** Src, void* Dest) const;

	virtual void Set(void* Src, void* Dest) const;

public:
	FORCEINLINE FProperty* GetProperty() const;

	FORCEINLINE void DestroyProperty();

public:
	FORCEINLINE bool Identical(const void* A, const void* B, uint32 PortFlags = 0) const;

	template <typename ValueType>
	FORCEINLINE auto ContainerPtrToValuePtr(void* ContainerPtr, const int32 ArrayIndex = 0) const;

	FORCEINLINE void DestroyValue(void* Dest) const;

	FORCEINLINE void InitializeValue_InContainer(void* Dest) const;

	FORCEINLINE int32 GetSize() const;

	FORCEINLINE uint32 GetValueTypeHash(const void* Src) const;

	virtual bool IsPrimitiveProperty() const;

protected:
	union
	{
		FProperty* Property = nullptr;

		FNumericProperty* NumericProperty;

		FByteProperty* ByteProperty;

		FInt8Property* Int8Property;

		FInt16Property* Int16Property;

		FIntProperty* IntProperty;

		FInt64Property* Int64Property;

		FUInt16Property* UUUInt16Property;

		FUInt32Property* UInt32Property;

		FUInt64Property* UUUInt64Property;

		FFloatProperty* FloatProperty;

		FDoubleProperty* DoubleProperty;

		FBoolProperty* BoolProperty;

		FObjectProperty* ObjectProperty;

		FWeakObjectProperty* WeakObjectProperty;

		FLazyObjectProperty* LazyObjectProperty;

		FSoftObjectProperty* SoftObjectProperty;

		FClassProperty* ClassProperty;

		FSoftClassProperty* SoftClassProperty;

		FInterfaceProperty* InterfaceProperty;

		FNameProperty* NameProperty;

		FStrProperty* StrProperty;

		FTextProperty* TextProperty;

		FArrayProperty* ArrayProperty;

		FEnumProperty* EnumProperty;

		FMapProperty* MapProperty;

		FSetProperty* SetProperty;

		FStructProperty* StructProperty;

		FDelegateProperty* DelegateProperty;

		FMulticastDelegateProperty* MulticastDelegateProperty;

		FMulticastInlineDelegateProperty* MulticastInlineDelegateProperty;

		FMulticastSparseDelegateProperty* MulticastSparseDelegateProperty;
	};
};

#include "FPropertyDescriptor.inl"
