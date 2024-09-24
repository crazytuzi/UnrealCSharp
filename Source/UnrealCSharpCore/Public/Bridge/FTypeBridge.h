#pragma once

#include "EPropertyTypeExtent.h"
#include "UEVersion.h"
#include "mono/metadata/object.h"

class UNREALCSHARPCORE_API FTypeBridge
{
public:
	static EPropertyTypeExtent GetPropertyType(MonoReflectionType* InReflectionType);

	static MonoClass* GetMonoClass(FProperty* InProperty);

	static MonoClass* GetMonoClass(const FByteProperty* InProperty);

	static MonoClass* GetMonoClass(const FClassProperty* InProperty);

	static MonoClass* GetMonoClass(const FObjectProperty* InProperty);

	static MonoClass* GetMonoClass(const FNameProperty*);

	static MonoClass* GetMonoClass(const FDelegateProperty* InProperty);

	static MonoClass* GetMonoClass(const FInterfaceProperty* InProperty);

	static MonoClass* GetMonoClass(const FStructProperty* InProperty);

	static MonoClass* GetMonoClass(const FArrayProperty* InProperty);

	static MonoClass* GetMonoClass(const FEnumProperty* InProperty);

	static MonoClass* GetMonoClass(const FStrProperty*);

	static MonoClass* GetMonoClass(const FTextProperty*);

	static MonoClass* GetMonoClass(const FMulticastDelegateProperty* InProperty);

	static MonoClass* GetMonoClass(const FWeakObjectProperty* InProperty);

	static MonoClass* GetMonoClass(const FLazyObjectProperty* InProperty);

	static MonoClass* GetMonoClass(const FSoftClassProperty* InProperty);

	static MonoClass* GetMonoClass(const FSoftObjectProperty* InProperty);

	static MonoClass* GetMonoClass(const FMapProperty* InProperty);

	static MonoClass* GetMonoClass(const FSetProperty* InProperty);

#if UE_F_OPTIONAL_PROPERTY
	static MonoClass* GetMonoClass(const FOptionalProperty* InProperty);
#endif

	static MonoClass* GetMonoClass(MonoClass* InGenericMonoClass, MonoClass* InTypeMonoClass);

	static MonoClass* GetMonoClass(MonoClass* InGenericMonoClass, MonoArray* InTypeMonoClassArray);

	template <auto IsSoftReference = false>
	static FProperty* Factory(MonoReflectionType* InReflectionType, const FFieldVariant& InOwner,
	                          const FName& InName, const EObjectFlags InObjectFlags);

	template <auto IsSoftReference = false>
	static FProperty* ManagedFactory(EPropertyTypeExtent InPropertyType, MonoReflectionType* InReflectionType,
	                                 const FFieldVariant& InOwner, const FName& InName,
	                                 const EObjectFlags InObjectFlags);

	static MonoReflectionType* GetType(MonoReflectionType* InReflectionType);

	static MonoReflectionType* GetGenericArgument(MonoObject* InMonoObject, int32 InIndex = 0);

	static MonoReflectionType* GetGenericArgument(MonoClass* InMonoClass, int32 InIndex = 0);

	static MonoReflectionType* GetGenericArgument(MonoType* InMonoType, int32 InIndex = 0);

	static MonoReflectionType* GetGenericArgument(MonoReflectionType* InReflectionType, int32 InIndex = 0);

	static MonoArray* GetGenericArguments(MonoObject* InMonoObject);

	static MonoArray* GetGenericArguments(MonoClass* InMonoClass);

	static MonoArray* GetGenericArguments(MonoType* InMonoType);

	static MonoArray* GetGenericArguments(MonoReflectionType* InReflectionType);

	static FString GetPathName(MonoReflectionType* InReflectionType);

	static FString GetGenericPathName(MonoReflectionType* InReflectionType);
};

#include "FTypeBridge.inl"
