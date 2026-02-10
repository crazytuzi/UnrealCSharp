#include "Bridge/FTypeBridge.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/ClassMacro.h"
#include "CoreMacro/FunctionMacro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Domain/FMonoDomain.h"
#include "Template/TGetArrayLength.inl"
#include "UEVersion.h"
#include "Reflection/FReflectionRegistry.h"
#if UE_F_OPTIONAL_PROPERTY
#include "UObject/PropertyOptional.h"
#endif

EPropertyTypeExtent FTypeBridge::GetPropertyType(MonoReflectionType* InReflectionType)
{
	const auto InMonoType = FMonoDomain::Reflection_Type_Get_Type(GetType(InReflectionType));

	const auto InMonoClass = FMonoDomain::Type_Get_Class(InMonoType);

	if (InMonoClass == FReflectionRegistry::Get().Get_Byte_Class())
	{
		return EPropertyTypeExtent::Byte;
	}

	if (InMonoClass == FReflectionRegistry::Get().Get_UInt16_Class())
	{
		return EPropertyTypeExtent::UInt16;
	}

	if (InMonoClass == FReflectionRegistry::Get().Get_UInt32_Class())
	{
		return EPropertyTypeExtent::UInt32;
	}

	if (InMonoClass == FReflectionRegistry::Get().Get_UInt64_Class())
	{
		return EPropertyTypeExtent::UInt64;
	}

	if (InMonoClass == FReflectionRegistry::Get().Get_SByte_Class())
	{
		return EPropertyTypeExtent::Int8;
	}

	if (InMonoClass == FReflectionRegistry::Get().Get_Int16_Class())
	{
		return EPropertyTypeExtent::Int16;
	}

	if (InMonoClass == FReflectionRegistry::Get().Get_Int32_Class())
	{
		return EPropertyTypeExtent::Int;
	}

	if (InMonoClass == FReflectionRegistry::Get().Get_Int64_Class())
	{
		return EPropertyTypeExtent::Int64;
	}

	if (InMonoClass == FReflectionRegistry::Get().Get_Boolean_Class())
	{
		return EPropertyTypeExtent::Bool;
	}

	if (InMonoClass == FReflectionRegistry::Get().Get_Single_Class())
	{
		return EPropertyTypeExtent::Float;
	}

	if (const auto FoundMonoClass = FReflectionRegistry::Get().Get_UClass_Class())
	{
		if (InMonoClass == FoundMonoClass)
		{
			return EPropertyTypeExtent::ClassReference;
		}
	}

	if (const auto FoundMonoClass = FReflectionRegistry::Get().Get_TSubclassOf_Class())
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			return EPropertyTypeExtent::SubclassOfReference;
		}
	}

	if (const auto FoundMonoClass = FReflectionRegistry::Get().Get_UObject_Class())
	{
		if (InMonoClass == FoundMonoClass ||
			FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			return EPropertyTypeExtent::ObjectReference;
		}
	}

	if (const auto FoundMonoClass = FReflectionRegistry::Get().Get_Name_Class())
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			return EPropertyTypeExtent::Name;
		}
	}

	if (const auto FoundMonoClass = FReflectionRegistry::Get().Get_TScriptInterface_Class())
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			return EPropertyTypeExtent::Interface;
		}
	}

	if (FMonoDomain::Class_Is_Subclass_Of(
		InMonoClass, FReflectionRegistry::Get().Get_Enum_Class(), false))
	{
		return EPropertyTypeExtent::Enum;
	}

	// @TODO
	if (FMonoDomain::Class_Get_Method_From_Name(
		InMonoClass, FUNCTION_STATIC_STRUCT, 0))
	{
		return EPropertyTypeExtent::Struct;
	}

	if (const auto FoundMonoClass = FReflectionRegistry::Get().Get_String_Class())
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			return EPropertyTypeExtent::String;
		}
	}

#if UE_F_UTF8_STR_PROPERTY
	if (const auto FoundMonoClass = FReflectionRegistry::Get().Get_Utf8String_Class())
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			return EPropertyTypeExtent::Utf8String;
		}
	}
#endif

#if UE_F_ANSI_STR_PROPERTY
	if (const auto FoundMonoClass = FReflectionRegistry::Get().Get_AnsiString_Class())
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			return EPropertyTypeExtent::AnsiString;
		}
	}
#endif

	if (const auto FoundMonoClass = FReflectionRegistry::Get().Get_Text_Class())
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			return EPropertyTypeExtent::Text;
		}
	}

	if (const auto FoundMonoClass = FReflectionRegistry::Get().Get_TWeakObjectPtr_Class())
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			return EPropertyTypeExtent::WeakObjectReference;
		}
	}

	if (const auto FoundMonoClass = FReflectionRegistry::Get().Get_TLazyObjectPtr_Class())
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			return EPropertyTypeExtent::LazyObjectReference;
		}
	}

	if (const auto FoundMonoClass = FReflectionRegistry::Get().Get_TSoftClassPtr_Class())
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			return EPropertyTypeExtent::SoftClassReference;
		}
	}

	if (const auto FoundMonoClass = FReflectionRegistry::Get().Get_TSoftObjectPtr_Class())
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			return EPropertyTypeExtent::SoftObjectReference;
		}
	}

	if (InMonoClass == FReflectionRegistry::Get().Get_Double_Class())
	{
		return EPropertyTypeExtent::Double;
	}

	if (const auto FoundMonoClass = FReflectionRegistry::Get().Get_TMap_Class())
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			return EPropertyTypeExtent::Map;
		}
	}

	if (const auto FoundMonoClass = FReflectionRegistry::Get().Get_TSet_Class())
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			return EPropertyTypeExtent::Set;
		}
	}

	if (const auto FoundMonoClass = FReflectionRegistry::Get().GetTArray_Class())
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			return EPropertyTypeExtent::Array;
		}
	}

	return EPropertyTypeExtent::None;
}

MonoClass* FTypeBridge::GetMonoClass(FProperty* InProperty)
{
	if (const auto ByteProperty = CastField<FByteProperty>(InProperty)) return GetMonoClass(ByteProperty);

	if (CastField<FUInt16Property>(InProperty))
	{
		return FReflectionRegistry::Get().Get_UInt16_Class();
	}

	if (CastField<FUInt32Property>(InProperty))
	{
		return FReflectionRegistry::Get().Get_UInt32_Class();
	}

	if (CastField<FUInt64Property>(InProperty))
	{
		return FReflectionRegistry::Get().Get_UInt64_Class();
	}

	if (CastField<FInt8Property>(InProperty))
	{
		return FReflectionRegistry::Get().Get_SByte_Class();
	}

	if (CastField<FInt16Property>(InProperty))
	{
		return FReflectionRegistry::Get().Get_Int16_Class();
	}

	if (CastField<FIntProperty>(InProperty))
	{
		return FReflectionRegistry::Get().Get_Int32_Class();
	}

	if (CastField<FInt64Property>(InProperty))
	{
		return FReflectionRegistry::Get().Get_Int64_Class();
	}

	if (CastField<FBoolProperty>(InProperty))
	{
		return FReflectionRegistry::Get().Get_Boolean_Class();
	}

	if (CastField<FFloatProperty>(InProperty))
	{
		return FReflectionRegistry::Get().Get_Single_Class();
	}

	if (const auto ClassProperty = CastField<FClassProperty>(InProperty))
	{
		return GetMonoClass(ClassProperty);
	}

	if (const auto ObjectProperty = CastField<FObjectProperty>(InProperty))
	{
		return GetMonoClass(ObjectProperty);
	}

	if (const auto NameProperty = CastField<FNameProperty>(InProperty))
	{
		return GetMonoClass(NameProperty);
	}

	if (const auto DelegateProperty = CastField<FDelegateProperty>(InProperty))
	{
		return GetMonoClass(DelegateProperty);
	}

	if (const auto InterfaceProperty = CastField<FInterfaceProperty>(InProperty))
	{
		return GetMonoClass(InterfaceProperty);
	}

	if (const auto StructProperty = CastField<FStructProperty>(InProperty))
	{
		return GetMonoClass(StructProperty);
	}

	if (const auto ArrayProperty = CastField<FArrayProperty>(InProperty))
	{
		return GetMonoClass(ArrayProperty);
	}

	if (const auto EnumProperty = CastField<FEnumProperty>(InProperty))
	{
		return GetMonoClass(EnumProperty);
	}

	if (const auto StrProperty = CastField<FStrProperty>(InProperty))
	{
		return GetMonoClass(StrProperty);
	}

	if (const auto TextProperty = CastField<FTextProperty>(InProperty))
	{
		return GetMonoClass(TextProperty);
	}

	if (const auto MulticastDelegateProperty = CastField<FMulticastDelegateProperty>(InProperty))
	{
		return GetMonoClass(MulticastDelegateProperty);
	}

	if (const auto MulticastInlineDelegateProperty = CastField<FMulticastInlineDelegateProperty>(InProperty))
	{
		return GetMonoClass(MulticastInlineDelegateProperty);
	}

	if (const auto MulticastSparseDelegateProperty = CastField<FMulticastSparseDelegateProperty>(InProperty))
	{
		return GetMonoClass(MulticastSparseDelegateProperty);
	}

	if (const auto WeakObjectProperty = CastField<FWeakObjectProperty>(InProperty))
	{
		return GetMonoClass(WeakObjectProperty);
	}

	if (const auto LazyObjectProperty = CastField<FLazyObjectProperty>(InProperty))
	{
		return GetMonoClass(LazyObjectProperty);
	}

	if (const auto SoftClassProperty = CastField<FSoftClassProperty>(InProperty))
	{
		return GetMonoClass(SoftClassProperty);
	}

	if (const auto SoftObjectProperty = CastField<FSoftObjectProperty>(InProperty))
	{
		return GetMonoClass(SoftObjectProperty);
	}

	if (CastField<FDoubleProperty>(InProperty))
	{
		return FReflectionRegistry::Get().Get_Double_Class();
	}

	if (const auto MapProperty = CastField<FMapProperty>(InProperty))
	{
		return GetMonoClass(MapProperty);
	}

	if (const auto SetProperty = CastField<FSetProperty>(InProperty))
	{
		return GetMonoClass(SetProperty);
	}

	// @TODO
	if (CastField<FFieldPathProperty>(InProperty))
	{
		return nullptr;
	}

#if UE_F_OPTIONAL_PROPERTY
	if (const auto OptionalProperty = CastField<FOptionalProperty>(InProperty))
	{
		return GetMonoClass(OptionalProperty);
	}
#endif

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FByteProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		return InProperty->Enum != nullptr
			       ? FReflectionRegistry::Get().GetClassReflection(InProperty->Enum)->GetClass()
			       : FReflectionRegistry::Get().Get_Byte_Class();
	}

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FClassProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		const auto FoundGenericMonoClass = FReflectionRegistry::Get().Get_TSubclassOf_Class();

		const auto FoundMonoClass = FReflectionRegistry::Get().GetClassReflection(InProperty->MetaClass);

		return GetMonoClass(FoundGenericMonoClass, FoundMonoClass->GetClass());
	}

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FObjectProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		return FReflectionRegistry::Get().GetClassReflection(InProperty->PropertyClass)->GetClass();
	}

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FNameProperty*)
{
	return FReflectionRegistry::Get().Get_Name_Class();
}

MonoClass* FTypeBridge::GetMonoClass(const FDelegateProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		return FMonoDomain::Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(InProperty),
			FUnrealCSharpFunctionLibrary::GetFullClass(InProperty));
	}

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FInterfaceProperty* InProperty)
{
	if (InProperty != nullptr)
	{
#if WITH_EDITOR
		if (FBlueprintSupport::IsClassPlaceholder(InProperty->InterfaceClass))
		{
			return nullptr;
		}
#endif

		const auto FoundGenericMonoClass = FReflectionRegistry::Get().Get_TScriptInterface_Class();

		const auto FoundMonoClass = FReflectionRegistry::Get().GetClassReflection(InProperty->InterfaceClass);

		return GetMonoClass(FoundGenericMonoClass, FoundMonoClass->GetClass());
	}

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FStructProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		return FReflectionRegistry::Get().GetClassReflection(InProperty->Struct)->GetClass();
	}

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FArrayProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		const auto FoundGenericMonoClass = FReflectionRegistry::Get().GetTArray_Class();

		const auto FoundMonoClass = GetMonoClass(InProperty->Inner);

		const auto FoundMonoType = FMonoDomain::Class_Get_Type(FoundMonoClass);

		const auto FoundReflectionType = FMonoDomain::Type_Get_Object(
			FoundMonoType);

		const auto ReflectionTypeMonoArray = FMonoDomain::Array_New(
			FReflectionRegistry::Get().Get_Object_Class(), 1);

		FMonoDomain::Array_Set(ReflectionTypeMonoArray, 0, FoundReflectionType);

		return GetMonoClass(FoundGenericMonoClass, FoundMonoClass);
	}

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FEnumProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		return FReflectionRegistry::Get().GetClassReflection(InProperty->GetEnum())->GetClass();
	}

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FStrProperty*)
{
	return FReflectionRegistry::Get().Get_String_Class();
}

#if UE_F_UTF8_STR_PROPERTY
MonoClass* FTypeBridge::GetMonoClass(const FUtf8StrProperty*)
{
	return FReflectionRegistry::Get().Get_Utf8String_Class();
}
#endif

#if UE_F_ANSI_STR_PROPERTY
MonoClass* FTypeBridge::GetMonoClass(const FAnsiStrProperty*)
{
	return FReflectionRegistry::Get().Get_AnsiString_Class();
}
#endif

MonoClass* FTypeBridge::GetMonoClass(const FTextProperty*)
{
	return FReflectionRegistry::Get().Get_Text_Class();
}

MonoClass* FTypeBridge::GetMonoClass(const FMulticastDelegateProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		return FMonoDomain::Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(InProperty),
			FUnrealCSharpFunctionLibrary::GetFullClass(InProperty));
	}

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FWeakObjectProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		const auto FoundGenericMonoClass = FReflectionRegistry::Get().Get_TWeakObjectPtr_Class();

		const auto FoundMonoClass = FReflectionRegistry::Get().GetClassReflection(InProperty->PropertyClass);

		return GetMonoClass(FoundGenericMonoClass, FoundMonoClass->GetClass());
	}

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FLazyObjectProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		const auto FoundGenericMonoClass = FReflectionRegistry::Get().Get_TLazyObjectPtr_Class();

		const auto FoundMonoClass = FReflectionRegistry::Get().GetClassReflection(InProperty->PropertyClass);

		return GetMonoClass(FoundGenericMonoClass, FoundMonoClass->GetClass());
	}

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FSoftClassProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		const auto FoundGenericMonoClass = FReflectionRegistry::Get().Get_TSoftClassPtr_Class();

		const auto FoundMonoClass = FReflectionRegistry::Get().GetClassReflection(InProperty->MetaClass);

		return GetMonoClass(FoundGenericMonoClass, FoundMonoClass->GetClass());
	}

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FSoftObjectProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		const auto FoundGenericMonoClass = FReflectionRegistry::Get().Get_TSoftObjectPtr_Class();

		const auto FoundMonoClass = FReflectionRegistry::Get().GetClassReflection(InProperty->PropertyClass);

		return GetMonoClass(FoundGenericMonoClass, FoundMonoClass->GetClass());
	}

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FMapProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		const auto FoundGenericMonoClass = FReflectionRegistry::Get().Get_TMap_Class();

		const auto FoundKeyMonoClass = GetMonoClass(InProperty->KeyProp);

		const auto FoundKeyMonoType = FMonoDomain::Class_Get_Type(
			FoundKeyMonoClass);

		const auto FoundKeyReflectionType = FMonoDomain::Type_Get_Object(
			FoundKeyMonoType);

		const auto FoundValueMonoClass = GetMonoClass(InProperty->ValueProp);

		const auto FoundValueMonoType = FMonoDomain::Class_Get_Type(
			FoundValueMonoClass);

		const auto FoundValueReflectionType = FMonoDomain::Type_Get_Object(
			FoundValueMonoType);

		const auto ReflectionTypeMonoArray = FMonoDomain::Array_New(
			FReflectionRegistry::Get().Get_Object_Class(), 2);

		FMonoDomain::Array_Set(ReflectionTypeMonoArray, 0, FoundKeyReflectionType);

		FMonoDomain::Array_Set(ReflectionTypeMonoArray, 1, FoundValueReflectionType);

		return GetMonoClass(FoundGenericMonoClass, ReflectionTypeMonoArray);
	}

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FSetProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		const auto FoundGenericMonoClass = FReflectionRegistry::Get().Get_TSet_Class();

		const auto FoundMonoClass = GetMonoClass(InProperty->ElementProp);

		const auto FoundMonoType = FMonoDomain::Class_Get_Type(FoundMonoClass);

		const auto FoundReflectionType = FMonoDomain::Type_Get_Object(
			FoundMonoType);

		const auto ReflectionTypeMonoArray = FMonoDomain::Array_New(
			FReflectionRegistry::Get().Get_Object_Class(), 1);

		FMonoDomain::Array_Set(ReflectionTypeMonoArray, 0, FoundReflectionType);

		return GetMonoClass(FoundGenericMonoClass, FoundMonoClass);
	}

	return nullptr;
}

#if UE_F_OPTIONAL_PROPERTY
MonoClass* FTypeBridge::GetMonoClass(const FOptionalProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		const auto FoundGenericMonoClass = FReflectionRegistry::Get().GetTOptional_Class();

		const auto FoundMonoClass = GetMonoClass(InProperty->GetValueProperty());

		const auto FoundMonoType = FMonoDomain::Class_Get_Type(FoundMonoClass);

		const auto FoundReflectionType = FMonoDomain::Type_Get_Object(
			FoundMonoType);

		const auto ReflectionTypeMonoArray = FMonoDomain::Array_New(
			FReflectionRegistry::Get().Get_Object_Class(), 1);

		FMonoDomain::Array_Set(ReflectionTypeMonoArray, 0, FoundReflectionType);

		return GetMonoClass(FoundGenericMonoClass, FoundMonoClass);
	}

	return nullptr;
}
#endif

MonoClass* FTypeBridge::GetMonoClass(MonoClass* InGenericMonoClass, MonoClass* InTypeMonoClass)
{
	const auto FoundGenericMonoType = FMonoDomain::Class_Get_Type(
		InGenericMonoClass);

	const auto FoundGenericReflectionType = FMonoDomain::Type_Get_Object(
		FoundGenericMonoType);

	const auto FoundMonoType = FMonoDomain::Class_Get_Type(InTypeMonoClass);

	const auto FoundReflectionType = FMonoDomain::Type_Get_Object(
		FoundMonoType);

	void* InParams[2];

	InParams[0] = FoundGenericReflectionType;

	const auto ReflectionTypeMonoArray = FMonoDomain::Array_New(
		FReflectionRegistry::Get().Get_Object_Class(), 1);

	FMonoDomain::Array_Set(ReflectionTypeMonoArray, 0, FoundReflectionType);

	InParams[1] = ReflectionTypeMonoArray;

	const auto UtilsMonoClass = FReflectionRegistry::Get().Get_Utils_Class();

	const auto CreateGenericTypeMethod = UtilsMonoClass->Get_Method_From_Name(FUNCTION_UTILS_MAKE_GENERIC_TYPE_INSTANCE, TGetArrayLength(InParams));

	const auto GenericClassMonoObject = FMonoDomain::Runtime_Invoke(
		CreateGenericTypeMethod->GetMethod(), nullptr, InParams);

	return FMonoDomain::Object_Get_Class(GenericClassMonoObject);
}

MonoClass* FTypeBridge::GetMonoClass(MonoClass* InGenericMonoClass, MonoArray* InTypeMonoClassArray)
{
	const auto FoundGenericMonoType = FMonoDomain::Class_Get_Type(
		InGenericMonoClass);

	const auto FoundGenericReflectionType = FMonoDomain::Type_Get_Object(
		FoundGenericMonoType);

	void* InParams[2];

	InParams[0] = FoundGenericReflectionType;

	InParams[1] = InTypeMonoClassArray;

	const auto UtilsMonoClass = FReflectionRegistry::Get().Get_Utils_Class();

	const auto CreateGenericTypeMethod = UtilsMonoClass->Get_Method_From_Name(
		FUNCTION_UTILS_MAKE_GENERIC_TYPE_INSTANCE, TGetArrayLength(InParams));

	const auto GenericClassMonoObject = FMonoDomain::Runtime_Invoke(
		CreateGenericTypeMethod->GetMethod(), nullptr, InParams);

	return FMonoDomain::Object_Get_Class(GenericClassMonoObject);
}

MonoReflectionType* FTypeBridge::GetType(MonoReflectionType* InReflectionType)
{
	auto InParams = static_cast<void*>(InReflectionType);

	const auto UtilsMonoClass = FReflectionRegistry::Get().Get_Utils_Class();

	const auto GetTypeMethod = UtilsMonoClass->Get_Method_From_Name(
		FUNCTION_UTILS_GET_TYPE, TGetArrayLength(InParams));

	return reinterpret_cast<MonoReflectionType*>(FMonoDomain::Runtime_Invoke(
		GetTypeMethod->GetMethod(), nullptr, &InParams));
}

MonoReflectionType* FTypeBridge::GetGenericArgument(MonoObject* InMonoObject, const int32 InIndex)
{
	return FMonoDomain::Array_Get<MonoReflectionType*>(
		GetGenericArguments(FMonoDomain::Object_Get_Class(InMonoObject)),
		InIndex);
}

MonoReflectionType* FTypeBridge::GetGenericArgument(MonoClass* InMonoClass, const int32 InIndex)
{
	return FMonoDomain::Array_Get<MonoReflectionType*>(GetGenericArguments(InMonoClass), InIndex);
}

MonoReflectionType* FTypeBridge::GetGenericArgument(MonoType* InMonoType, const int32 InIndex)
{
	return FMonoDomain::Array_Get<MonoReflectionType*>(GetGenericArguments(InMonoType), InIndex);
}

MonoReflectionType* FTypeBridge::GetGenericArgument(MonoReflectionType* InReflectionType, const int32 InIndex)
{
	return FMonoDomain::Array_Get<MonoReflectionType*>(GetGenericArguments(InReflectionType), InIndex);
}

MonoArray* FTypeBridge::GetGenericArguments(MonoObject* InMonoObject)
{
	return GetGenericArguments(FMonoDomain::Object_Get_Class(InMonoObject));
}

MonoArray* FTypeBridge::GetGenericArguments(MonoClass* InMonoClass)
{
	return GetGenericArguments(FMonoDomain::Class_Get_Type(InMonoClass));
}

MonoArray* FTypeBridge::GetGenericArguments(MonoType* InMonoType)
{
	return GetGenericArguments(FMonoDomain::Type_Get_Object(InMonoType));
}

MonoArray* FTypeBridge::GetGenericArguments(MonoReflectionType* InReflectionType)
{
	const auto UtilsMonoClass = FReflectionRegistry::Get().Get_Utils_Class();

	auto InParams = static_cast<void*>(InReflectionType);

	const auto GetGenericArgumentsMethod = UtilsMonoClass->Get_Method_From_Name(
			FUNCTION_UTILS_GET_GENERIC_ARGUMENTS, TGetArrayLength(InParams));

	return reinterpret_cast<MonoArray*>(FMonoDomain::Runtime_Invoke(
		GetGenericArgumentsMethod->GetMethod(), nullptr, &InParams));
}

FString FTypeBridge::GetPathName(MonoReflectionType* InReflectionType)
{
	const auto UtilsMonoClass = FReflectionRegistry::Get().Get_Utils_Class();

	auto InParams = static_cast<void*>(InReflectionType);

	const auto GetPathNameMonoMethod = UtilsMonoClass->Get_Method_From_Name(
		FUNCTION_UTILS_GET_PATH_NAME, TGetArrayLength(InParams));

	const auto PathNameMonoObject = FMonoDomain::Runtime_Invoke(
		GetPathNameMonoMethod->GetMethod(), nullptr, &InParams);

	const auto PathNameMonoString = FMonoDomain::Object_To_String(
		PathNameMonoObject, nullptr);

	return UTF8_TO_TCHAR(FMonoDomain::String_To_UTF8(PathNameMonoString));
}

FString FTypeBridge::GetGenericPathName(MonoReflectionType* InReflectionType)
{
	return GetPathName(GetGenericArgument(InReflectionType));
}
