#pragma once

#include "EPropertyTypeExtent.h"
#include "UEVersion.h"
#include "mono/metadata/object.h"

class FTypeBridge
{
public:
	static EPropertyTypeExtent GetPropertyType(MonoReflectionType* InReflectionType);

	static UNREALCSHARPCORE_API MonoClass* GetMonoClass(FProperty* InProperty);

	static UNREALCSHARPCORE_API MonoClass* GetMonoClass(const FByteProperty* InProperty);

	static UNREALCSHARPCORE_API MonoClass* GetMonoClass(const FClassProperty* InProperty);

	static UNREALCSHARPCORE_API MonoClass* GetMonoClass(const FObjectProperty* InProperty);

	static UNREALCSHARPCORE_API MonoClass* GetMonoClass(const FNameProperty*);

	static UNREALCSHARPCORE_API MonoClass* GetMonoClass(const FDelegateProperty* InProperty);

	static UNREALCSHARPCORE_API MonoClass* GetMonoClass(const FInterfaceProperty* InProperty);

	static UNREALCSHARPCORE_API MonoClass* GetMonoClass(const FStructProperty* InProperty);

	static UNREALCSHARPCORE_API MonoClass* GetMonoClass(const FArrayProperty* InProperty);

	static UNREALCSHARPCORE_API MonoClass* GetMonoClass(const FEnumProperty* InProperty);

	static UNREALCSHARPCORE_API MonoClass* GetMonoClass(const FStrProperty*);

	static UNREALCSHARPCORE_API MonoClass* GetMonoClass(const FTextProperty*);

	static UNREALCSHARPCORE_API MonoClass* GetMonoClass(const FMulticastDelegateProperty* InProperty);

	static UNREALCSHARPCORE_API MonoClass* GetMonoClass(const FWeakObjectProperty* InProperty);

	static UNREALCSHARPCORE_API MonoClass* GetMonoClass(const FLazyObjectProperty* InProperty);

	static UNREALCSHARPCORE_API MonoClass* GetMonoClass(const FSoftClassProperty* InProperty);

	static UNREALCSHARPCORE_API MonoClass* GetMonoClass(const FSoftObjectProperty* InProperty);

	static UNREALCSHARPCORE_API MonoClass* GetMonoClass(const FMapProperty* InProperty);

	static UNREALCSHARPCORE_API MonoClass* GetMonoClass(const FSetProperty* InProperty);

#if UE_F_OPTIONAL_PROPERTY
	static UNREALCSHARPCORE_API MonoClass* GetMonoClass(const FOptionalProperty* InProperty);
#endif

	static UNREALCSHARPCORE_API MonoClass* GetMonoClass(MonoClass* InGenericMonoClass, MonoClass* InTypeMonoClass);

	static UNREALCSHARPCORE_API MonoClass* GetMonoClass(MonoClass* InGenericMonoClass, MonoArray* InTypeMonoClassArray);

	static UNREALCSHARPCORE_API FProperty* Factory(MonoReflectionType* InReflectionType, const FFieldVariant& InOwner,
	                                               const FName& InName, const EObjectFlags InObjectFlags);

	static FProperty* ManagedFactory(EPropertyTypeExtent InPropertyType, MonoReflectionType* InReflectionType,
	                                 const FFieldVariant& InOwner, const FName& InName,
	                                 const EObjectFlags InObjectFlags);

	static MonoReflectionType* GetType(MonoReflectionType* InReflectionType);

	static UNREALCSHARPCORE_API MonoReflectionType* GetGenericArgument(MonoObject* InMonoObject, int32 InIndex = 0);

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
