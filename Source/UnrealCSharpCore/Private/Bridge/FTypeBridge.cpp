#include "Bridge/FTypeBridge.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/ClassMacro.h"
#include "CoreMacro/FunctionMacro.h"
#include "CoreMacro/MonoMacro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Domain/FMonoDomain.h"
#include "Template/TGetArrayLength.inl"
#include "UEVersion.h"
#if UE_F_OPTIONAL_PROPERTY
#include "UObject/PropertyOptional.h"
#endif

EPropertyTypeExtent FTypeBridge::GetPropertyType(MonoReflectionType* InReflectionType)
{
	InReflectionType = GetType(InReflectionType);

	const auto InMonoType = FMonoDomain::Reflection_Type_Get_Type(
		InReflectionType);

	const auto InMonoClass = FMonoDomain::Type_Get_Class(InMonoType);

	if (InMonoClass == FMonoDomain::Get_Byte_Class())
	{
		return EPropertyTypeExtent::Byte;
	}

	if (InMonoClass == FMonoDomain::Get_UInt16_Class())
	{
		return EPropertyTypeExtent::UInt16;
	}

	if (InMonoClass == FMonoDomain::Get_UInt32_Class())
	{
		return EPropertyTypeExtent::UInt32;
	}

	if (InMonoClass == FMonoDomain::Get_UInt64_Class())
	{
		return EPropertyTypeExtent::UInt64;
	}

	if (InMonoClass == FMonoDomain::Get_SByte_Class())
	{
		return EPropertyTypeExtent::Int8;
	}

	if (InMonoClass == FMonoDomain::Get_Int16_Class())
	{
		return EPropertyTypeExtent::Int16;
	}

	if (InMonoClass == FMonoDomain::Get_Int32_Class())
	{
		return EPropertyTypeExtent::Int;
	}

	if (InMonoClass == FMonoDomain::Get_Int64_Class())
	{
		return EPropertyTypeExtent::Int64;
	}

	if (InMonoClass == FMonoDomain::Get_Boolean_Class())
	{
		return EPropertyTypeExtent::Bool;
	}

	if (InMonoClass == FMonoDomain::Get_Single_Class())
	{
		return EPropertyTypeExtent::Float;
	}

	if (const auto FoundMonoClass = FMonoDomain::Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(UClass::StaticClass()),
		FUnrealCSharpFunctionLibrary::GetFullClass(UClass::StaticClass())))
	{
		if (InMonoClass == FoundMonoClass)
		{
			return EPropertyTypeExtent::ClassReference;
		}
	}

	if (const auto FoundMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), GENERIC_T_SUB_CLASS_OF))
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			return EPropertyTypeExtent::SubclassOfReference;
		}
	}

	if (const auto FoundMonoClass = FMonoDomain::Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(UObject::StaticClass()),
		FUnrealCSharpFunctionLibrary::GetFullClass(UObject::StaticClass())))
	{
		if (InMonoClass == FoundMonoClass ||
			FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			return EPropertyTypeExtent::ObjectReference;
		}
	}

	if (const auto FoundMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), CLASS_F_NAME))
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			return EPropertyTypeExtent::Name;
		}
	}

	if (const auto FoundMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), GENERIC_T_SCRIPT_INTERFACE))
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			return EPropertyTypeExtent::Interface;
		}
	}

	if (FMonoDomain::Class_Is_Subclass_Of(
		InMonoClass, FMonoDomain::Get_Enum_Class(), false))
	{
		return EPropertyTypeExtent::Enum;
	}

	if (const auto InType = FMonoDomain::Reflection_Type_Get_Type(
		InReflectionType))
	{
		if (const auto InClass = FMonoDomain::Type_Get_Class(InType))
		{
			if (FMonoDomain::Class_Get_Method_From_Name(
				InClass, FUNCTION_STATIC_STRUCT, 0))
			{
				return EPropertyTypeExtent::Struct;
			}
		}
	}

	if (const auto FoundMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), CLASS_F_STRING))
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			return EPropertyTypeExtent::String;
		}
	}

	if (const auto FoundMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), CLASS_F_TEXT))
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			return EPropertyTypeExtent::Text;
		}
	}

	if (const auto FoundMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), GENERIC_T_WEAK_OBJECT_PTR))
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			return EPropertyTypeExtent::WeakObjectReference;
		}
	}

	if (const auto FoundMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), GENERIC_T_LAZY_OBJECT_PTR))
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			return EPropertyTypeExtent::LazyObjectReference;
		}
	}

	if (const auto FoundMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), GENERIC_T_SOFT_CLASS_PTR))
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			return EPropertyTypeExtent::SoftClassReference;
		}
	}

	if (const auto FoundMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), GENERIC_T_SOFT_OBJECT_PTR))
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			return EPropertyTypeExtent::SoftObjectReference;
		}
	}

	if (InMonoClass == FMonoDomain::Get_Double_Class())
	{
		return EPropertyTypeExtent::Double;
	}

	if (const auto FoundMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), GENERIC_T_MAP))
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			return EPropertyTypeExtent::Map;
		}
	}

	if (const auto FoundMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), GENERIC_T_SET))
	{
		if (FMonoDomain::Class_Is_Subclass_Of(InMonoClass, FoundMonoClass, false))
		{
			return EPropertyTypeExtent::Set;
		}
	}

	if (const auto FoundMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), GENERIC_T_ARRAY))
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
		return FMonoDomain::Get_UInt16_Class();
	}

	if (CastField<FUInt32Property>(InProperty))
	{
		return FMonoDomain::Get_UInt32_Class();
	}

	if (CastField<FUInt64Property>(InProperty))
	{
		return FMonoDomain::Get_UInt64_Class();
	}

	if (CastField<FInt8Property>(InProperty))
	{
		return FMonoDomain::Get_SByte_Class();
	}

	if (CastField<FInt16Property>(InProperty))
	{
		return FMonoDomain::Get_Int16_Class();
	}

	if (CastField<FIntProperty>(InProperty))
	{
		return FMonoDomain::Get_Int32_Class();
	}

	if (CastField<FInt64Property>(InProperty))
	{
		return FMonoDomain::Get_Int64_Class();
	}

	if (CastField<FBoolProperty>(InProperty))
	{
		return FMonoDomain::Get_Boolean_Class();
	}

	if (CastField<FFloatProperty>(InProperty))
	{
		return FMonoDomain::Get_Single_Class();
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
		return FMonoDomain::Get_Double_Class();
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
			       ? FMonoDomain::Class_From_Name(
				       FUnrealCSharpFunctionLibrary::GetClassNameSpace(InProperty->Enum),
				       FUnrealCSharpFunctionLibrary::GetFullClass(InProperty->Enum))
			       : FMonoDomain::Get_Byte_Class();
	}

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FClassProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		const auto FoundGenericMonoClass = FMonoDomain::Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), GENERIC_T_SUB_CLASS_OF);

		const auto FoundMonoClass = FMonoDomain::Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(InProperty->MetaClass),
			FUnrealCSharpFunctionLibrary::GetFullClass(InProperty->MetaClass));

		return GetMonoClass(FoundGenericMonoClass, FoundMonoClass);
	}

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FObjectProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		return FMonoDomain::Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(InProperty->PropertyClass),
			FUnrealCSharpFunctionLibrary::GetFullClass(InProperty->PropertyClass));
	}

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FNameProperty*)
{
	return FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), CLASS_F_NAME);
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

		const auto FoundGenericMonoClass = FMonoDomain::Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), GENERIC_T_SCRIPT_INTERFACE);

		const auto FoundMonoClass = FMonoDomain::Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(InProperty->InterfaceClass),
			FUnrealCSharpFunctionLibrary::GetFullInterface(InProperty->InterfaceClass));

		return GetMonoClass(FoundGenericMonoClass, FoundMonoClass);
	}

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FStructProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		return FMonoDomain::Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(InProperty->Struct),
			FUnrealCSharpFunctionLibrary::GetFullClass(InProperty->Struct));
	}

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FArrayProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		const auto FoundGenericMonoClass = FMonoDomain::Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), GENERIC_T_ARRAY);

		const auto FoundMonoClass = GetMonoClass(InProperty->Inner);

		const auto FoundMonoType = FMonoDomain::Class_Get_Type(FoundMonoClass);

		const auto FoundReflectionType = FMonoDomain::Type_Get_Object(
			FoundMonoType);

		const auto ReflectionTypeMonoArray = FMonoDomain::Array_New(
			FMonoDomain::Get_Object_Class(), 1);

		ARRAY_SET(ReflectionTypeMonoArray, MonoReflectionType*, 0, FoundReflectionType);

		return GetMonoClass(FoundGenericMonoClass, FoundMonoClass);
	}

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FEnumProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		return FMonoDomain::Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(InProperty->GetEnum()),
			FUnrealCSharpFunctionLibrary::GetFullClass(InProperty->GetEnum()));
	}

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FStrProperty*)
{
	return FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), CLASS_F_STRING);
}

MonoClass* FTypeBridge::GetMonoClass(const FTextProperty*)
{
	return FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), CLASS_F_TEXT);
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
		const auto FoundGenericMonoClass = FMonoDomain::Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), GENERIC_T_WEAK_OBJECT_PTR);

		const auto FoundMonoClass = FMonoDomain::Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(InProperty->PropertyClass),
			FUnrealCSharpFunctionLibrary::GetFullClass(InProperty->PropertyClass));

		return GetMonoClass(FoundGenericMonoClass, FoundMonoClass);
	}

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FLazyObjectProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		const auto FoundGenericMonoClass = FMonoDomain::Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), GENERIC_T_LAZY_OBJECT_PTR);

		const auto FoundMonoClass = FMonoDomain::Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(InProperty->PropertyClass),
			FUnrealCSharpFunctionLibrary::GetFullClass(InProperty->PropertyClass));

		return GetMonoClass(FoundGenericMonoClass, FoundMonoClass);
	}

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FSoftClassProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		const auto FoundGenericMonoClass = FMonoDomain::Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), GENERIC_T_SOFT_CLASS_PTR);

		const auto FoundMonoClass = FMonoDomain::Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(InProperty->MetaClass),
			FUnrealCSharpFunctionLibrary::GetFullClass(InProperty->MetaClass));

		return GetMonoClass(FoundGenericMonoClass, FoundMonoClass);
	}

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FSoftObjectProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		const auto FoundGenericMonoClass = FMonoDomain::Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), GENERIC_T_SOFT_OBJECT_PTR);

		const auto FoundMonoClass = FMonoDomain::Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(InProperty->PropertyClass),
			FUnrealCSharpFunctionLibrary::GetFullClass(InProperty->PropertyClass));

		return GetMonoClass(FoundGenericMonoClass, FoundMonoClass);
	}

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FMapProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		const auto FoundGenericMonoClass = FMonoDomain::Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), GENERIC_T_MAP);

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
			FMonoDomain::Get_Object_Class(), 2);

		ARRAY_SET(ReflectionTypeMonoArray, MonoReflectionType*, 0, FoundKeyReflectionType);

		ARRAY_SET(ReflectionTypeMonoArray, MonoReflectionType*, 1, FoundValueReflectionType);

		return GetMonoClass(FoundGenericMonoClass, ReflectionTypeMonoArray);
	}

	return nullptr;
}

MonoClass* FTypeBridge::GetMonoClass(const FSetProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		const auto FoundGenericMonoClass = FMonoDomain::Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), GENERIC_T_SET);

		const auto FoundMonoClass = GetMonoClass(InProperty->ElementProp);

		const auto FoundMonoType = FMonoDomain::Class_Get_Type(FoundMonoClass);

		const auto FoundReflectionType = FMonoDomain::Type_Get_Object(
			FoundMonoType);

		const auto ReflectionTypeMonoArray = FMonoDomain::Array_New(
			FMonoDomain::Get_Object_Class(), 1);

		ARRAY_SET(ReflectionTypeMonoArray, MonoReflectionType*, 0, FoundReflectionType);

		return GetMonoClass(FoundGenericMonoClass, FoundMonoClass);
	}

	return nullptr;
}

#if UE_F_OPTIONAL_PROPERTY
MonoClass* FTypeBridge::GetMonoClass(const FOptionalProperty* InProperty)
{
	if (InProperty != nullptr)
	{
		const auto FoundGenericMonoClass = FMonoDomain::Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), GENERIC_T_OPTIONAL);

		const auto FoundMonoClass = GetMonoClass(InProperty->GetValueProperty());

		const auto FoundMonoType = FMonoDomain::Class_Get_Type(FoundMonoClass);

		const auto FoundReflectionType = FMonoDomain::Type_Get_Object(
			FoundMonoType);

		const auto ReflectionTypeMonoArray = FMonoDomain::Array_New(
			FMonoDomain::Get_Object_Class(), 1);

		ARRAY_SET(ReflectionTypeMonoArray, MonoReflectionType*, 0, FoundReflectionType);

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
		FMonoDomain::Get_Object_Class(), 1);

	ARRAY_SET(ReflectionTypeMonoArray, MonoReflectionType*, 0, FoundReflectionType);

	InParams[1] = ReflectionTypeMonoArray;

	const auto UtilsMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), CLASS_UTILS);

	const auto CreateGenericTypeMethod = FMonoDomain::Class_Get_Method_From_Name(
		UtilsMonoClass, FUNCTION_UTILS_MAKE_GENERIC_TYPE_INSTANCE, TGetArrayLength(InParams));

	const auto GenericClassMonoObject = FMonoDomain::Runtime_Invoke(
		CreateGenericTypeMethod, nullptr, InParams);

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

	const auto UtilsMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), CLASS_UTILS);

	const auto CreateGenericTypeMethod = FMonoDomain::Class_Get_Method_From_Name(
		UtilsMonoClass, FUNCTION_UTILS_MAKE_GENERIC_TYPE_INSTANCE, TGetArrayLength(InParams));

	const auto GenericClassMonoObject = FMonoDomain::Runtime_Invoke(
		CreateGenericTypeMethod, nullptr, InParams);

	return FMonoDomain::Object_Get_Class(GenericClassMonoObject);
}

FProperty* FTypeBridge::Factory(MonoReflectionType* InReflectionType, const FFieldVariant& InOwner,
                                const FName& InName, const EObjectFlags InObjectFlags)
{
	switch (const auto PropertyType = GetPropertyType(InReflectionType); PropertyType)
	{
	case EPropertyTypeExtent::Byte: return new FByteProperty(InOwner, InName, InObjectFlags);

	case EPropertyTypeExtent::UInt16: return new FUInt16Property(InOwner, InName, InObjectFlags);

	case EPropertyTypeExtent::UInt32: return new FUInt32Property(InOwner, InName, InObjectFlags);

	case EPropertyTypeExtent::UInt64: return new FUInt64Property(InOwner, InName, InObjectFlags);

	case EPropertyTypeExtent::Int8: return new FInt8Property(InOwner, InName, InObjectFlags);

	case EPropertyTypeExtent::Int16: return new FInt16Property(InOwner, InName, InObjectFlags);

	case EPropertyTypeExtent::Int: return new FIntProperty(InOwner, InName, InObjectFlags);

	case EPropertyTypeExtent::Int64: return new FInt64Property(InOwner, InName, InObjectFlags);

	case EPropertyTypeExtent::Bool: return new FBoolProperty(InOwner, InName, InObjectFlags);

	case EPropertyTypeExtent::Float: return new FFloatProperty(InOwner, InName, InObjectFlags);

	case EPropertyTypeExtent::ClassReference:
		{
			return ManagedFactory(PropertyType, InReflectionType, InOwner, InName, InObjectFlags);
		}

	case EPropertyTypeExtent::SubclassOfReference:
		{
			return ManagedFactory(PropertyType, InReflectionType, InOwner, InName, InObjectFlags);
		}

	case EPropertyTypeExtent::ObjectReference:
		{
			return ManagedFactory(PropertyType, InReflectionType, InOwner, InName, InObjectFlags);
		}

	case EPropertyTypeExtent::Name: return new FNameProperty(InOwner, InName, InObjectFlags);

	case EPropertyTypeExtent::Interface:
		{
			return ManagedFactory(PropertyType, InReflectionType, InOwner, InName, InObjectFlags);
		}

	case EPropertyTypeExtent::Struct:
		{
			return ManagedFactory(PropertyType, InReflectionType, InOwner, InName, InObjectFlags);
		}

	case EPropertyTypeExtent::Enum:
		{
			return ManagedFactory(PropertyType, InReflectionType, InOwner, InName, InObjectFlags);
		}

	case EPropertyTypeExtent::String: return new FStrProperty(InOwner, InName, InObjectFlags);

	case EPropertyTypeExtent::Text: return new FTextProperty(InOwner, InName, InObjectFlags);

	case EPropertyTypeExtent::WeakObjectReference:
		{
			return ManagedFactory(PropertyType, InReflectionType, InOwner, InName, InObjectFlags);
		}

	case EPropertyTypeExtent::LazyObjectReference:
		{
			return ManagedFactory(PropertyType, InReflectionType, InOwner, InName, InObjectFlags);
		}

	case EPropertyTypeExtent::SoftClassReference:
		{
			return ManagedFactory(PropertyType, InReflectionType, InOwner, InName, InObjectFlags);
		}

	case EPropertyTypeExtent::SoftObjectReference:
		{
			return ManagedFactory(PropertyType, InReflectionType, InOwner, InName, InObjectFlags);
		}

	case EPropertyTypeExtent::Double: return new FDoubleProperty(InOwner, InName, InObjectFlags);

	case EPropertyTypeExtent::Map:
		{
			return ManagedFactory(PropertyType, InReflectionType, InOwner, InName, InObjectFlags);
		}

	case EPropertyTypeExtent::Set:
		{
			return ManagedFactory(PropertyType, InReflectionType, InOwner, InName, InObjectFlags);
		}

	case EPropertyTypeExtent::Array:
		{
			return ManagedFactory(PropertyType, InReflectionType, InOwner, InName, InObjectFlags);
		}

	default: return nullptr;
	}
}

FProperty* FTypeBridge::ManagedFactory(const EPropertyTypeExtent InPropertyType,
                                       MonoReflectionType* InReflectionType, const FFieldVariant& InOwner,
                                       const FName& InName, const EObjectFlags InObjectFlags)
{
	switch (InPropertyType)
	{
	case EPropertyTypeExtent::ClassReference:
		{
			const auto PathName = GetGenericPathName(InReflectionType);

			const auto ClassProperty = new FClassProperty(InOwner, InName, InObjectFlags);

			ClassProperty->MetaClass = UObject::StaticClass();

			return ClassProperty;
		}

	case EPropertyTypeExtent::SubclassOfReference:
		{
			const auto PathName = GetGenericPathName(InReflectionType);

			const auto InClass = LoadObject<UClass>(nullptr, *FString(PathName));

			const auto ClassProperty = new FClassProperty(InOwner, InName, InObjectFlags);

			ClassProperty->SetPropertyFlags(CPF_UObjectWrapper);

			ClassProperty->MetaClass = InClass;

			return ClassProperty;
		}

	case EPropertyTypeExtent::ObjectReference:
		{
			const auto PathName = GetPathName(InReflectionType);

			const auto InClass = LoadObject<UClass>(nullptr, *PathName);

			const auto ObjectProperty = new FObjectProperty(InOwner, InName, InObjectFlags);

			ObjectProperty->PropertyClass = InClass;

			return ObjectProperty;
		}

	case EPropertyTypeExtent::Interface:
		{
			const auto PathName = GetGenericPathName(InReflectionType);

			const auto InClass = LoadObject<UClass>(nullptr, *FString(PathName));

			const auto InterfaceProperty = new FInterfaceProperty(InOwner, InName, InObjectFlags);

			InterfaceProperty->InterfaceClass = InClass;

			return InterfaceProperty;
		}

	case EPropertyTypeExtent::Struct:
		{
			const auto PathName = GetPathName(InReflectionType);

			const auto InScriptStruct = LoadObject<UScriptStruct>(nullptr, *PathName);

			const auto StructProperty = new FStructProperty(InOwner, InName, InObjectFlags);

			StructProperty->ElementSize = InScriptStruct->GetStructureSize();

			StructProperty->Struct = InScriptStruct;

			return StructProperty;
		}

	case EPropertyTypeExtent::Map:
		{
			const auto MapProperty = new FMapProperty(InOwner, InName, InObjectFlags);

			MapProperty->KeyProp = Factory(GetGenericArgument(InReflectionType), MapProperty, "",
			                               EObjectFlags::RF_Transient);

			MapProperty->ValueProp = Factory(GetGenericArgument(InReflectionType, 1), MapProperty, "",
			                                 EObjectFlags::RF_Transient);

			return MapProperty;
		}

	case EPropertyTypeExtent::Set:
		{
			const auto SetProperty = new FSetProperty(InOwner, InName, InObjectFlags);

			SetProperty->ElementProp = Factory(GetGenericArgument(InReflectionType), SetProperty, "",
			                                   EObjectFlags::RF_Transient);

			return SetProperty;
		}

	case EPropertyTypeExtent::Array:
		{
			const auto ArrayProperty = new FArrayProperty(InOwner, InName, InObjectFlags);

			ArrayProperty->Inner = Factory(GetGenericArgument(InReflectionType), ArrayProperty, "",
			                               EObjectFlags::RF_Transient);

			return ArrayProperty;
		}

	case EPropertyTypeExtent::Enum:
		{
			const auto PathName = GetPathName(InReflectionType);

			const auto InEnum = LoadObject<UEnum>(nullptr, *PathName);

			const auto EnumProperty = new FEnumProperty(InOwner, InName, InObjectFlags);

			const auto InType = FMonoDomain::Reflection_Type_Get_Type(
				GetType(InReflectionType));

			const auto UnderlyingType = FMonoDomain::
				Type_Get_Underlying_Type(InType);

			const auto UnderlyingReflectionType = FMonoDomain::Type_Get_Object(
				UnderlyingType);

			const auto UnderlyingProperty = Factory(UnderlyingReflectionType, EnumProperty, "",
			                                        EObjectFlags::RF_NoFlags);

			EnumProperty->ElementSize = UnderlyingProperty->ElementSize;

			EnumProperty->SetEnum(InEnum);

			EnumProperty->AddCppProperty(UnderlyingProperty);

			return EnumProperty;
		}

	case EPropertyTypeExtent::WeakObjectReference:
		{
			const auto PathName = GetGenericPathName(InReflectionType);

			const auto InClass = LoadObject<UClass>(nullptr, *FString(PathName));

			const auto WeakObjectProperty = new FWeakObjectProperty(InOwner, InName, InObjectFlags);

			WeakObjectProperty->PropertyClass = InClass;

			return WeakObjectProperty;
		}

	case EPropertyTypeExtent::LazyObjectReference:
		{
			const auto PathName = GetGenericPathName(InReflectionType);

			const auto InClass = LoadObject<UClass>(nullptr, *FString(PathName));

			const auto LazyObjectProperty = new FLazyObjectProperty(InOwner, InName, InObjectFlags);

			LazyObjectProperty->PropertyClass = InClass;

			return LazyObjectProperty;
		}

	case EPropertyTypeExtent::SoftClassReference:
		{
			const auto PathName = GetGenericPathName(InReflectionType);

			const auto InClass = LoadObject<UClass>(nullptr, *FString(PathName));

			const auto SoftClassProperty = new FSoftClassProperty(InOwner, InName, InObjectFlags);

			SoftClassProperty->MetaClass = InClass;

			return SoftClassProperty;
		}

	case EPropertyTypeExtent::SoftObjectReference:
		{
			const auto PathName = GetGenericPathName(InReflectionType);

			const auto InClass = LoadObject<UClass>(nullptr, *FString(PathName));

			const auto SoftObjectProperty = new FSoftObjectProperty(InOwner, InName, InObjectFlags);

			SoftObjectProperty->PropertyClass = InClass;

			return SoftObjectProperty;
		}

	default: return nullptr;
	}
}

MonoReflectionType* FTypeBridge::GetType(MonoReflectionType* InReflectionType)
{
	auto InParams = static_cast<void*>(InReflectionType);

	const auto UtilsMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), CLASS_UTILS);

	const auto GetTypeMethod = FMonoDomain::Class_Get_Method_From_Name(
		UtilsMonoClass, FUNCTION_UTILS_GET_TYPE, TGetArrayLength(InParams));

	return reinterpret_cast<MonoReflectionType*>(FMonoDomain::Runtime_Invoke(
		GetTypeMethod, nullptr, &InParams));
}

MonoReflectionType* FTypeBridge::GetGenericArgument(MonoObject* InMonoObject, const int32 InIndex)
{
	return ARRAY_GET(
		GetGenericArguments(FMonoDomain::Object_Get_Class(InMonoObject)),
		MonoReflectionType*, InIndex);
}

MonoReflectionType* FTypeBridge::GetGenericArgument(MonoClass* InMonoClass, const int32 InIndex)
{
	return ARRAY_GET(GetGenericArguments(InMonoClass), MonoReflectionType*, InIndex);
}

MonoReflectionType* FTypeBridge::GetGenericArgument(MonoType* InMonoType, const int32 InIndex)
{
	return ARRAY_GET(GetGenericArguments(InMonoType), MonoReflectionType*, InIndex);
}

MonoReflectionType* FTypeBridge::GetGenericArgument(MonoReflectionType* InReflectionType, const int32 InIndex)
{
	return ARRAY_GET(GetGenericArguments(InReflectionType), MonoReflectionType*, InIndex);
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
	const auto UtilsMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), CLASS_UTILS);

	auto InParams = static_cast<void*>(InReflectionType);

	const auto GetGenericArgumentsMethod = FMonoDomain::
		Class_Get_Method_From_Name(
			UtilsMonoClass, FUNCTION_UTILS_GET_GENERIC_ARGUMENTS, TGetArrayLength(InParams));

	return reinterpret_cast<MonoArray*>(FMonoDomain::Runtime_Invoke(
		GetGenericArgumentsMethod, nullptr, &InParams));
}

FString FTypeBridge::GetPathName(MonoReflectionType* InReflectionType)
{
	const auto UtilsMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), CLASS_UTILS);

	auto InParams = static_cast<void*>(InReflectionType);

	const auto GetPathNameMonoMethod = FMonoDomain::Class_Get_Method_From_Name(
		UtilsMonoClass, FUNCTION_UTILS_GET_PATH_NAME, TGetArrayLength(InParams));

	const auto PathNameMonoObject = FMonoDomain::Runtime_Invoke(
		GetPathNameMonoMethod, nullptr, &InParams);

	const auto PathNameMonoString = FMonoDomain::Object_To_String(
		PathNameMonoObject, nullptr);

	return UTF8_TO_TCHAR(FMonoDomain::String_To_UTF8(PathNameMonoString));
}

FString FTypeBridge::GetGenericPathName(MonoReflectionType* InReflectionType)
{
	return GetPathName(GetGenericArgument(InReflectionType));
}
