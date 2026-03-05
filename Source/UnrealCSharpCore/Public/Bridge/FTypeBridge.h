#pragma once

#include "EPropertyTypeExtent.h"
#include "UEVersion.h"
#include "mono/metadata/object.h"

class FClassReflection;

class UNREALCSHARPCORE_API FTypeBridge
{
public:
	static EPropertyTypeExtent GetPropertyType(const FClassReflection* InClass);

	static FClassReflection* MakeGenericTypeInstance(const FClassReflection* InGeneric, const FClassReflection* InType);

	static FClassReflection* MakeGenericTypeInstance(const FClassReflection* InGeneric, MonoArray* InTypeArray);

	static FClassReflection* GetClass(FProperty* InProperty);

	static FClassReflection* GetClass(const FByteProperty* InProperty);

	static FClassReflection* GetClass(const FClassProperty* InProperty);

	static FClassReflection* GetClass(const FObjectProperty* InProperty);

	static FClassReflection* GetClass(const FNameProperty*);

	static FClassReflection* GetClass(const FDelegateProperty* InProperty);

	static FClassReflection* GetClass(const FInterfaceProperty* InProperty);

	static FClassReflection* GetClass(const FStructProperty* InProperty);

	static FClassReflection* GetClass(const FArrayProperty* InProperty);

	static FClassReflection* GetClass(const FEnumProperty* InProperty);

	static FClassReflection* GetClass(const FStrProperty*);

#if UE_F_UTF8_STR_PROPERTY
	static FClassReflection* GetClass(const FUtf8StrProperty*);
#endif

#if UE_F_ANSI_STR_PROPERTY
	static FClassReflection* GetClass(const FAnsiStrProperty*);
#endif

	static FClassReflection* GetClass(const FTextProperty*);

	static FClassReflection* GetClass(const FMulticastDelegateProperty* InProperty);

	static FClassReflection* GetClass(const FWeakObjectProperty* InProperty);

	static FClassReflection* GetClass(const FLazyObjectProperty* InProperty);

	static FClassReflection* GetClass(const FSoftClassProperty* InProperty);

	static FClassReflection* GetClass(const FSoftObjectProperty* InProperty);

	static FClassReflection* GetClass(const FMapProperty* InProperty);

	static FClassReflection* GetClass(const FSetProperty* InProperty);

#if UE_F_OPTIONAL_PROPERTY
	static FClassReflection* GetClass(const FOptionalProperty* InProperty);
#endif

	template <auto IsSoftReference = false>
	static FProperty* Factory(FClassReflection* InClass, const FFieldVariant& InOwner,
	                          const FName& InName, const EObjectFlags InObjectFlags);

	template <auto IsSoftReference = false>
	static FProperty* ManagedFactory(EPropertyTypeExtent InPropertyType, FClassReflection* InClass,
	                                 const FFieldVariant& InOwner, const FName& InName,
	                                 const EObjectFlags InObjectFlags);
};

#include "FTypeBridge.inl"
