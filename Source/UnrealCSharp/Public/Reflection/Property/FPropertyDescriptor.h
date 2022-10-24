#pragma once

enum
{
	CPT_Enum = CPT_Unused_Index_21,
	CPT_Array = CPT_Unused_Index_22,
};

class FPropertyDescriptor
{
public:
	static FPropertyDescriptor* Factory(FProperty* InProperty);

public:
	virtual ~FPropertyDescriptor() = default;

	explicit FPropertyDescriptor(FProperty* InProperty);

public:
	virtual void Get(void* Src, void* Dest) const
	{
	};

	virtual void Set(void* Src, void* Dest) const
	{
	};

	virtual void Get(UObject* Src, void* Dest) const;

	virtual void Set(void* Src, UObject* Dest) const;

	virtual FProperty* GetProperty() { return Property; }

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

		FArrayProperty* ArrayProperty;

		FMapProperty* MapProperty;

		FSetProperty* SetProperty;

		FStructProperty* StructProperty;

		FDelegateProperty* DelegateProperty;

		FMulticastDelegateProperty* MulticastDelegateProperty;

		FMulticastInlineDelegateProperty* MulticastInlineDelegateProperty;

		FMulticastSparseDelegateProperty* MulticastSparseDelegateProperty;
	};
};
