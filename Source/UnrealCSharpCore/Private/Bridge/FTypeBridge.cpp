#include "Bridge/FTypeBridge.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/FunctionMacro.h"
#include "Domain/FMonoDomain.h"
#include "Template/TGetArrayLength.inl"
#include "Reflection/FReflectionRegistry.h"
#include "UEVersion.h"
#if UE_F_OPTIONAL_PROPERTY
#include "UObject/PropertyOptional.h"
#endif

EPropertyTypeExtent FTypeBridge::GetPropertyType(const FClassReflection* InClass)
{
	const auto TypeDefinition = InClass->GetTypeDefinition();

	if (TypeDefinition->IsAssignableFrom(FReflectionRegistry::Get().GetByteClass()))
	{
		return EPropertyTypeExtent::Byte;
	}

	if (TypeDefinition->IsAssignableFrom(FReflectionRegistry::Get().GetUInt16Class()))
	{
		return EPropertyTypeExtent::UInt16;
	}

	if (TypeDefinition->IsAssignableFrom(FReflectionRegistry::Get().GetUInt32Class()))
	{
		return EPropertyTypeExtent::UInt32;
	}

	if (TypeDefinition->IsAssignableFrom(FReflectionRegistry::Get().GetUInt64Class()))
	{
		return EPropertyTypeExtent::UInt64;
	}

	if (TypeDefinition->IsAssignableFrom(FReflectionRegistry::Get().GetSByteClass()))
	{
		return EPropertyTypeExtent::Int8;
	}

	if (TypeDefinition->IsAssignableFrom(FReflectionRegistry::Get().GetInt16Class()))
	{
		return EPropertyTypeExtent::Int16;
	}

	if (TypeDefinition->IsAssignableFrom(FReflectionRegistry::Get().GetInt32Class()))
	{
		return EPropertyTypeExtent::Int;
	}

	if (TypeDefinition->IsAssignableFrom(FReflectionRegistry::Get().GetInt64Class()))
	{
		return EPropertyTypeExtent::Int64;
	}

	if (TypeDefinition->IsAssignableFrom(FReflectionRegistry::Get().GetBooleanClass()))
	{
		return EPropertyTypeExtent::Bool;
	}

	if (TypeDefinition->IsAssignableFrom(FReflectionRegistry::Get().GetSingleClass()))
	{
		return EPropertyTypeExtent::Float;
	}

	if (TypeDefinition->IsAssignableFrom(FReflectionRegistry::Get().GetUClassClass()))
	{
		return EPropertyTypeExtent::ClassReference;
	}

	if (TypeDefinition->IsAssignableFrom(FReflectionRegistry::Get().GetTSubclassOfClass()))
	{
		return EPropertyTypeExtent::SubclassOfReference;
	}

	if (TypeDefinition->IsAssignableFrom(FReflectionRegistry::Get().GetUObjectClass()))
	{
		return EPropertyTypeExtent::ObjectReference;
	}

	if (TypeDefinition->IsAssignableFrom(FReflectionRegistry::Get().GetNameClass()))
	{
		return EPropertyTypeExtent::Name;
	}

	if (TypeDefinition->IsAssignableFrom(FReflectionRegistry::Get().GetTScriptInterfaceClass()))
	{
		return EPropertyTypeExtent::Interface;
	}

	if (TypeDefinition->IsAssignableFrom(FReflectionRegistry::Get().GetEnumClass()))
	{
		return EPropertyTypeExtent::Enum;
	}

	if (TypeDefinition->GetMethod(FUNCTION_STATIC_STRUCT, 0) != nullptr)
	{
		return EPropertyTypeExtent::Struct;
	}

	if (TypeDefinition->IsAssignableFrom(FReflectionRegistry::Get().GetStringClass()))
	{
		return EPropertyTypeExtent::String;
	}

#if UE_F_UTF8_STR_PROPERTY
	if (TypeDefinition->IsAssignableFrom(FReflectionRegistry::Get().GetUtf8StringClass()))
	{
		return EPropertyTypeExtent::Utf8String;
	}
#endif

#if UE_F_ANSI_STR_PROPERTY
	if (TypeDefinition->IsAssignableFrom(FReflectionRegistry::Get().GetAnsiStringClass()))
	{
		return EPropertyTypeExtent::AnsiString;
	}
#endif

	if (TypeDefinition->IsAssignableFrom(FReflectionRegistry::Get().GetTextClass()))
	{
		return EPropertyTypeExtent::Text;
	}

	if (TypeDefinition->IsAssignableFrom(FReflectionRegistry::Get().GetTWeakObjectPtrClass()))
	{
		return EPropertyTypeExtent::WeakObjectReference;
	}

	if (TypeDefinition->IsAssignableFrom(FReflectionRegistry::Get().GetTLazyObjectPtrClass()))
	{
		return EPropertyTypeExtent::LazyObjectReference;
	}

	if (TypeDefinition->IsAssignableFrom(FReflectionRegistry::Get().GetTSoftClassPtrClass()))
	{
		return EPropertyTypeExtent::SoftClassReference;
	}

	if (TypeDefinition->IsAssignableFrom(FReflectionRegistry::Get().GetTSoftObjectPtrClass()))
	{
		return EPropertyTypeExtent::SoftObjectReference;
	}

	if (TypeDefinition->IsAssignableFrom(FReflectionRegistry::Get().GetDoubleClass()))
	{
		return EPropertyTypeExtent::Double;
	}

	if (TypeDefinition->IsAssignableFrom(FReflectionRegistry::Get().GetTMapClass()))
	{
		return EPropertyTypeExtent::Map;
	}

	if (TypeDefinition->IsAssignableFrom(FReflectionRegistry::Get().GetTSetClass()))
	{
		return EPropertyTypeExtent::Set;
	}

	if (TypeDefinition->IsAssignableFrom(FReflectionRegistry::Get().GetTArrayClass()))
	{
		return EPropertyTypeExtent::Array;
	}

	return EPropertyTypeExtent::None;
}

FClassReflection* FTypeBridge::MakeGenericTypeInstance(const FClassReflection* InGeneric,
                                                       const FClassReflection* InType)
{
	const auto FoundReflectionType = InType->GetReflectionType();

	const auto ReflectionTypeArray = FReflectionRegistry::Get().GetObjectClass()->NewArray(1);

	FMonoDomain::Array_Set(ReflectionTypeArray, 0, FoundReflectionType);

	return MakeGenericTypeInstance(InGeneric, ReflectionTypeArray);
}

FClassReflection* FTypeBridge::MakeGenericTypeInstance(const FClassReflection* InGeneric, MonoArray* InTypeArray)
{
	void* InParams[2];

	InParams[0] = InGeneric->GetReflectionType();

	InParams[1] = InTypeArray;

	const auto UtilsClass = FReflectionRegistry::Get().GetUtilsClass();

	const auto MakeGenericTypeInstanceMethod = UtilsClass->GetMethod(
		FUNCTION_UTILS_MAKE_GENERIC_TYPE_INSTANCE, TGetArrayLength(InParams));

	return FReflectionRegistry::Get().GetClass(
		(MonoReflectionType*)MakeGenericTypeInstanceMethod->Runtime_Invoke(nullptr, InParams));
}

FClassReflection* FTypeBridge::GetClass(FProperty* InProperty)
{
	if (const auto ByteProperty = CastField<FByteProperty>(InProperty)) return GetClass(ByteProperty);

	if (CastField<FUInt16Property>(InProperty))
	{
		return FReflectionRegistry::Get().GetUInt16Class();
	}

	if (CastField<FUInt32Property>(InProperty))
	{
		return FReflectionRegistry::Get().GetUInt32Class();
	}

	if (CastField<FUInt64Property>(InProperty))
	{
		return FReflectionRegistry::Get().GetUInt64Class();
	}

	if (CastField<FInt8Property>(InProperty))
	{
		return FReflectionRegistry::Get().GetSByteClass();
	}

	if (CastField<FInt16Property>(InProperty))
	{
		return FReflectionRegistry::Get().GetInt16Class();
	}

	if (CastField<FIntProperty>(InProperty))
	{
		return FReflectionRegistry::Get().GetInt32Class();
	}

	if (CastField<FInt64Property>(InProperty))
	{
		return FReflectionRegistry::Get().GetInt64Class();
	}

	if (CastField<FBoolProperty>(InProperty))
	{
		return FReflectionRegistry::Get().GetBooleanClass();
	}

	if (CastField<FFloatProperty>(InProperty))
	{
		return FReflectionRegistry::Get().GetSingleClass();
	}

	if (const auto ClassProperty = CastField<FClassProperty>(InProperty))
	{
		return GetClass(ClassProperty);
	}

	if (const auto ObjectProperty = CastField<FObjectProperty>(InProperty))
	{
		return GetClass(ObjectProperty);
	}

	if (const auto NameProperty = CastField<FNameProperty>(InProperty))
	{
		return GetClass(NameProperty);
	}

	if (const auto DelegateProperty = CastField<FDelegateProperty>(InProperty))
	{
		return GetClass(DelegateProperty);
	}

	if (const auto InterfaceProperty = CastField<FInterfaceProperty>(InProperty))
	{
		return GetClass(InterfaceProperty);
	}

	if (const auto StructProperty = CastField<FStructProperty>(InProperty))
	{
		return GetClass(StructProperty);
	}

	if (const auto ArrayProperty = CastField<FArrayProperty>(InProperty))
	{
		return GetClass(ArrayProperty);
	}

	if (const auto EnumProperty = CastField<FEnumProperty>(InProperty))
	{
		return GetClass(EnumProperty);
	}

	if (const auto StrProperty = CastField<FStrProperty>(InProperty))
	{
		return GetClass(StrProperty);
	}

	if (const auto TextProperty = CastField<FTextProperty>(InProperty))
	{
		return GetClass(TextProperty);
	}

	if (const auto MulticastDelegateProperty = CastField<FMulticastDelegateProperty>(InProperty))
	{
		return GetClass(MulticastDelegateProperty);
	}

	if (const auto MulticastInlineDelegateProperty = CastField<FMulticastInlineDelegateProperty>(InProperty))
	{
		return GetClass(MulticastInlineDelegateProperty);
	}

	if (const auto MulticastSparseDelegateProperty = CastField<FMulticastSparseDelegateProperty>(InProperty))
	{
		return GetClass(MulticastSparseDelegateProperty);
	}

	if (const auto WeakObjectProperty = CastField<FWeakObjectProperty>(InProperty))
	{
		return GetClass(WeakObjectProperty);
	}

	if (const auto LazyObjectProperty = CastField<FLazyObjectProperty>(InProperty))
	{
		return GetClass(LazyObjectProperty);
	}

	if (const auto SoftClassProperty = CastField<FSoftClassProperty>(InProperty))
	{
		return GetClass(SoftClassProperty);
	}

	if (const auto SoftObjectProperty = CastField<FSoftObjectProperty>(InProperty))
	{
		return GetClass(SoftObjectProperty);
	}

	if (CastField<FDoubleProperty>(InProperty))
	{
		return FReflectionRegistry::Get().GetDoubleClass();
	}

	if (const auto MapProperty = CastField<FMapProperty>(InProperty))
	{
		return GetClass(MapProperty);
	}

	if (const auto SetProperty = CastField<FSetProperty>(InProperty))
	{
		return GetClass(SetProperty);
	}

	// @TODO
	if (CastField<FFieldPathProperty>(InProperty))
	{
		return nullptr;
	}

#if UE_F_OPTIONAL_PROPERTY
	if (const auto OptionalProperty = CastField<FOptionalProperty>(InProperty))
	{
		return GetClass(OptionalProperty);
	}
#endif

	return nullptr;
}

FClassReflection* FTypeBridge::GetClass(const FByteProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		return InProperty->Enum != nullptr
			       ? FReflectionRegistry::Get().GetClass(InProperty->Enum)
			       : FReflectionRegistry::Get().GetByteClass();
	}

	return nullptr;
}

FClassReflection* FTypeBridge::GetClass(const FClassProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		const auto FoundGenericClass = FReflectionRegistry::Get().GetTSubclassOfClass();

		const auto FoundClass = FReflectionRegistry::Get().GetClass(InProperty->MetaClass);

		return MakeGenericTypeInstance(FoundGenericClass, FoundClass);
	}

	return nullptr;
}

FClassReflection* FTypeBridge::GetClass(const FObjectProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		return FReflectionRegistry::Get().GetClass(InProperty->PropertyClass);
	}

	return nullptr;
}

FClassReflection* FTypeBridge::GetClass(const FNameProperty*)
{
	return FReflectionRegistry::Get().GetNameClass();
}

FClassReflection* FTypeBridge::GetClass(const FDelegateProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		return FReflectionRegistry::Get().GetClass(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(InProperty),
			FUnrealCSharpFunctionLibrary::GetFullClass(InProperty));
	}

	return nullptr;
}

FClassReflection* FTypeBridge::GetClass(const FInterfaceProperty* InProperty)
{
	if (InProperty != nullptr)
	{
#if WITH_EDITOR
		if (FBlueprintSupport::IsClassPlaceholder(InProperty->InterfaceClass))
		{
			return nullptr;
		}
#endif

		const auto FoundGenericClass = FReflectionRegistry::Get().GetTScriptInterfaceClass();

		const auto FoundClass = FReflectionRegistry::Get().GetClass(InProperty->InterfaceClass);

		return MakeGenericTypeInstance(FoundGenericClass, FoundClass);
	}

	return nullptr;
}

FClassReflection* FTypeBridge::GetClass(const FStructProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		return FReflectionRegistry::Get().GetClass(InProperty->Struct);
	}

	return nullptr;
}

FClassReflection* FTypeBridge::GetClass(const FArrayProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		const auto FoundGenericClass = FReflectionRegistry::Get().GetTArrayClass();

		const auto FoundClass = GetClass(InProperty->Inner);

		return MakeGenericTypeInstance(FoundGenericClass, FoundClass);
	}

	return nullptr;
}

FClassReflection* FTypeBridge::GetClass(const FEnumProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		return FReflectionRegistry::Get().GetClass(InProperty->GetEnum());
	}

	return nullptr;
}

FClassReflection* FTypeBridge::GetClass(const FStrProperty*)
{
	return FReflectionRegistry::Get().GetStringClass();
}

#if UE_F_UTF8_STR_PROPERTY
FClassReflection* FTypeBridge::GetClass(const FUtf8StrProperty*)
{
	return FReflectionRegistry::Get().GetUtf8StringClass();
}
#endif

#if UE_F_ANSI_STR_PROPERTY
FClassReflection* FTypeBridge::GetClass(const FAnsiStrProperty*)
{
	return FReflectionRegistry::Get().GetAnsiStringClass();
}
#endif

FClassReflection* FTypeBridge::GetClass(const FTextProperty*)
{
	return FReflectionRegistry::Get().GetTextClass();
}

FClassReflection* FTypeBridge::GetClass(const FMulticastDelegateProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		return FReflectionRegistry::Get().GetClass(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(InProperty),
			FUnrealCSharpFunctionLibrary::GetFullClass(InProperty));
	}

	return nullptr;
}

FClassReflection* FTypeBridge::GetClass(const FWeakObjectProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		const auto FoundGenericClass = FReflectionRegistry::Get().GetTWeakObjectPtrClass();

		const auto FoundClass = FReflectionRegistry::Get().GetClass(InProperty->PropertyClass);

		return MakeGenericTypeInstance(FoundGenericClass, FoundClass);
	}

	return nullptr;
}

FClassReflection* FTypeBridge::GetClass(const FLazyObjectProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		const auto FoundGenericClass = FReflectionRegistry::Get().GetTLazyObjectPtrClass();

		const auto FoundClass = FReflectionRegistry::Get().GetClass(InProperty->PropertyClass);

		return MakeGenericTypeInstance(FoundGenericClass, FoundClass);
	}

	return nullptr;
}

FClassReflection* FTypeBridge::GetClass(const FSoftClassProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		const auto FoundGenericClass = FReflectionRegistry::Get().GetTSoftClassPtrClass();

		const auto FoundClass = FReflectionRegistry::Get().GetClass(InProperty->MetaClass);

		return MakeGenericTypeInstance(FoundGenericClass, FoundClass);
	}

	return nullptr;
}

FClassReflection* FTypeBridge::GetClass(const FSoftObjectProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		const auto FoundGenericClass = FReflectionRegistry::Get().GetTSoftObjectPtrClass();

		const auto FoundClass = FReflectionRegistry::Get().GetClass(InProperty->PropertyClass);

		return MakeGenericTypeInstance(FoundGenericClass, FoundClass);
	}

	return nullptr;
}

FClassReflection* FTypeBridge::GetClass(const FMapProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		const auto FoundGenericClass = FReflectionRegistry::Get().GetTMapClass();

		const auto FoundKeyClass = GetClass(InProperty->KeyProp);

		const auto FoundValueClass = GetClass(InProperty->ValueProp);

		const auto ReflectionTypeArray = FReflectionRegistry::Get().GetObjectClass()->NewArray(2);

		FMonoDomain::Array_Set(ReflectionTypeArray, 0, FoundKeyClass->GetReflectionType());

		FMonoDomain::Array_Set(ReflectionTypeArray, 1, FoundValueClass->GetReflectionType());

		return MakeGenericTypeInstance(FoundGenericClass, ReflectionTypeArray);
	}

	return nullptr;
}

FClassReflection* FTypeBridge::GetClass(const FSetProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		const auto FoundGenericClass = FReflectionRegistry::Get().GetTSetClass();

		const auto FoundClass = GetClass(InProperty->ElementProp);

		return MakeGenericTypeInstance(FoundGenericClass, FoundClass);
	}

	return nullptr;
}

#if UE_F_OPTIONAL_PROPERTY
FClassReflection* FTypeBridge::GetClass(const FOptionalProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		const auto FoundGenericClass = FReflectionRegistry::Get().GetTOptionalClass();

		const auto FoundClass = GetClass(InProperty->GetValueProperty());

		return MakeGenericTypeInstance(FoundGenericClass, FoundClass);
	}

	return nullptr;
}
#endif
