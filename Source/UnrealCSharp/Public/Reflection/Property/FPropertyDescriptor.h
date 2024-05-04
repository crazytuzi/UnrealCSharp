#pragma once

#include "Bridge/EPropertyTypeExtent.h"
#include "UEVersion.h"

class FPropertyDescriptor
{
public:
	static EPropertyTypeExtent GetPropertyType(const FProperty* Property);

	static FPropertyDescriptor* Factory(FProperty* InProperty);

public:
	virtual ~FPropertyDescriptor() = default;

	explicit FPropertyDescriptor(FProperty* InProperty);

public:
	virtual void Get(void* Src, void** Dest) const;

	virtual void Get(void* Src, void* Dest) const;

	virtual void Set(void* Src, void* Dest) const;

public:
	FORCEINLINE FProperty* GetProperty() const;

	FORCEINLINE void DestroyProperty();

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

#if UE_F_OPTIONAL_PROPERTY
		FOptionalProperty* OptionalProperty;
#endif
	};
};

#include "FPropertyDescriptor.inl"
