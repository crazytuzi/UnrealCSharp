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

	virtual void Set(void* Src, void* Dest) const;

	FProperty* GetProperty() const;

	template <typename ValueType>
	FORCEINLINE ValueType* ContainerPtrToValuePtr(void* ContainerPtr, const int32 ArrayIndex = 0) const
	{
		return Property != nullptr ? Property->ContainerPtrToValuePtr<ValueType>(ContainerPtr, ArrayIndex) : nullptr;
	}

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
